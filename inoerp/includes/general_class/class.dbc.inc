<?php

class dbc {

 public $connection;
 public $rollback;

// public $pending_transaction;

 function __construct() {
  if(!(DB_SERVER)){
   return false;
  }
	try {
	 $this->connection = new PDO('mysql:host=' . DB_SERVER . '; dbname=' . DB_NAME . ';charset=utf8', DB_USER, DB_PASS);
	 $this->connection->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
//	 $this->connection->setAttribute(PDO::ATTR_PERSISTENT, true);
	 $this->connection->setAttribute(PDO::ATTR_AUTOCOMMIT, false);
    $this->rollback = false;
//	 $this->pending_transaction = true;
	 $this->connection->beginTransaction();
	} catch (PDOException $e) {
	 print "Data Base Connection Error!: <br> Modify the database settings @ includes/basics/dbsettings.inc file & reload the page"
   . "<br>" . $e->getMessage() . "<br/>";
	 die();
	}
 }

 public function confirm() {
	if ($this->rollback) {
	$this->connection->rollBack();
	 echo "<div class='rollback_msg'>All the transactions have been rolled back because of the above specified reasons."
	 . "<br>Fix all the issues before trying the transaction again! </div>";
	} else {
	 $this->connection->commit();
	 	}
	$this->connection->beginTransaction();
 }

//ddlexecute is used for all delete/update/drop
 public function ddlexecute($sql = '') {
	if (!empty($sql)) {
	 $stmt = $this->connection->prepare($sql);
	 try {
		$stmt->execute();
		return true;
	 } catch (PDOException $e) {
		print "DDL failed! : " . $e->getMessage() . "<br/>";
		return false;
	 }
	}
 }

 //iexecute is used for all insert operation
 public function iexecute($sql = '') {
	if (!empty($sql)) {
	 $prepare = $this->connection->prepare($sql);
	 try {
		$prepare->execute();
		$result = $this->connection->lastInsertId();
		return $result;
	 } catch (PDOException $e) {
		print " Execution failed!: " . $e->getMessage() . "<br/>";
	 }
	}
 }

 public function sexecute($sql = '') {
	if (!empty($sql)) {
	 $prepare = $this->connection->prepare($sql);
	 try {
		$prepare->execute();
		$result = $prepare->fetchAll(PDO::FETCH_CLASS);
		return $result;
	 } catch (PDOException $e) {
		print " Execution failed!: " . $e->getMessage() . "<br/>";
	 }
	}
 }

 public function close_connection() {
	$this->connection = null;
 }

}

$dbc = new dbc();
?>