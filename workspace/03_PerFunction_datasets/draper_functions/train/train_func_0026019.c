db_open(db_handle_t *db, const char * filename)
{
  FILE *fp = NULL;
  int returnVal = 0;

  if ( NULL == filename )
  {
    DBG_PRINT(DBG_WARN, ("Null Passed to Filename"));
    returnVal = DB_NULL_ERROR;
    goto OPEN_ERR;
  }


#ifndef SQL_LITE
  if ( db->mode == WRITE_MODE ) {
    fp = fopen(filename, "r+b");

    if ( NULL == fp ) {

      fp = fopen(filename, "w+b");
    }
  }


  if ( db->mode == READ_MODE )
    fp = fopen(filename, "rb" );

  if ( NULL == fp )
  {
    DBG_PRINT(DBG_WARN, ("Unable to Open File"));
    returnVal = DB_OPEN_ERROR;
    goto OPEN_ERR;
  }

  db->handle = fp;

#endif

#ifdef SQL_LITE
  char *errMsg = NULL;
  char sql[BUF_SIZE];
  memset(sql, 0, BUF_SIZE);

  returnVal = sqlite3_open(filename, &db->handle);
  if ( returnVal )
  {
    DBG_PRINT(DBG_WARN, ("Cannot Open Database %s\n", sqlite3_errmsg(db->handle)));
    returnVal = SQLITE_OPEN_ERROR;
    db->handle = NULL;
    goto OPEN_ERR;
  }


#ifdef ALLOW_DUPLICATES
  sprintf(sql, "CREATE TABLE IF NOT EXISTS %s ( id int8 )", TABLE_NAME);
#else
  sprintf(sql, "CREATE TABLE IF NOT EXISTS %s ( id int8 primary key )", TABLE_NAME);
#endif
  returnVal = sqlite3_exec(db->handle, sql, NULL, 0, &errMsg);

  if ( returnVal ) {
    DBG_PRINT(DBG_WARN, ("Error While Creating Table %s\n", errMsg));
    sqlite3_free(errMsg);
    returnVal = CREATE_TABLE_ERROR;
    goto OPEN_ERR;
  }

#endif
  db->fileName = filename;
OPEN_ERR:
  return returnVal;
}
