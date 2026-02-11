sqlite_get_table(
  sqlite *db,
  const char *zSql,
  char ***pazResult,
  int *pnRow,
  int *pnColumn,
  char **pzErrMsg
){
  int rc;
  TabResult res;
  if( pazResult==0 ){ return SQLITE_ERROR; }
  *pazResult = 0;
  if( pnColumn ) *pnColumn = 0;
  if( pnRow ) *pnRow = 0;
  res.zErrMsg = 0;
  res.nResult = 0;
  res.nRow = 0;
  res.nColumn = 0;
  res.nData = 1;
  res.nAlloc = 20;
  res.rc = SQLITE_OK;
  res.azResult = malloc( sizeof(char*)*res.nAlloc );
  if( res.azResult==0 ){
    return SQLITE_NOMEM;
  }
  res.azResult[0] = 0;
  rc = sqlite_exec(db, zSql, sqlite_get_table_cb, &res, pzErrMsg);
  if( res.azResult ){
    res.azResult[0] = (char*)res.nData;
  }
  if( rc==SQLITE_ABORT ){
    sqlite_free_table(&res.azResult[1]);
    if( res.zErrMsg ){
      if( pzErrMsg ){
        free(*pzErrMsg);
        *pzErrMsg = res.zErrMsg;
        sqliteStrRealloc(pzErrMsg);
      }else{
        sqliteFree(res.zErrMsg);
      }
    }
    return res.rc;
  }
  sqliteFree(res.zErrMsg);
  if( rc!=SQLITE_OK ){
    sqlite_free_table(&res.azResult[1]);
    return rc;
  }
  if( res.nAlloc>res.nData ){
    char **azNew;
    azNew = realloc( res.azResult, sizeof(char*)*(res.nData+1) );
    if( azNew==0 ){
      sqlite_free_table(&res.azResult[1]);
      return SQLITE_NOMEM;
    }
    res.nAlloc = res.nData+1;
    res.azResult = azNew;
  }
  *pazResult = &res.azResult[1];
  if( pnColumn ) *pnColumn = res.nColumn;
  if( pnRow ) *pnRow = res.nRow;
  return rc;
}
