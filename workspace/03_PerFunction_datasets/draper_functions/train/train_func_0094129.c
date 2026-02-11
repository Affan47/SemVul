db_find( db_handle_t *db, uint64_t cardid)
{

  int returnVal = 0;
  if ( NULL == db) {

    DBG_PRINT(DBG_WARN, ("Db handle is NULL"));
    returnVal = HANDLE_NULL_ERROR;
    goto FIND_ERR;
  }

#ifdef SQL_LITE
  char sql[BUF_SIZE];
  char *errMsg;
  int  counter = 0;

  memset(sql, 0, BUF_SIZE);
  sprintf(sql, "SELECT * FROM %s WHERE id = %llu", TABLE_NAME, cardid);
  returnVal = sqlite3_exec(db->handle, sql, callback, (void *)&counter, &errMsg);

  if ( returnVal ) {
    DBG_PRINT(DBG_WARN, ("Error While Searching id = %llu. %s", cardid, errMsg));
    sqlite3_free(errMsg);
    returnVal = FIND_ERROR;
    goto FIND_ERR;
  }

  if ( counter == 0 )
    returnVal = 1;
  else
    returnVal = 0;
#else

  fseek(db->handle, 0L, SEEK_END);
  if ( 0L == ftell(db->handle) ) {
    DBG_PRINT(DBG_WARN, ("Empty File"));
    returnVal = 1;
    goto FIND_ERR;
  }

  fseek(db->handle, 0L, SEEK_SET);
  returnVal = traverse(db->handle, cardid);
  if ( returnVal == DUPLICATE_KEY_ERROR ) {
    returnVal = 0;
  } else {
    returnVal = 1;
  }

#endif

FIND_ERR:
  return returnVal;
}
