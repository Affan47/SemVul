run_table_dump_query(
  struct callback_data *p,
  const char *zSelect,
  const char *zFirstRow
){
  sqlite3_stmt *pSelect;
  int rc;
  int nResult;
  int i;
  const char *z;
  rc = sqlite3_prepare(p->db, zSelect, -1, &pSelect, 0);
  if( rc!=SQLITE_OK || !pSelect ){
    fprintf(p->out, "/**** ERROR: (%d) %s *****/\n", rc, sqlite3_errmsg(p->db));
    p->nErr++;
    return rc;
  }
  rc = sqlite3_step(pSelect);
  nResult = sqlite3_column_count(pSelect);
  while( rc==SQLITE_ROW ){
    if( zFirstRow ){
      fprintf(p->out, "%s", zFirstRow);
      zFirstRow = 0;
    }
    z = (const char*)sqlite3_column_text(pSelect, 0);
    fprintf(p->out, "%s", z);
    for(i=1; i<nResult; i++){
      fprintf(p->out, ",%s", sqlite3_column_text(pSelect, i));
    }
    if( z==0 ) z = "";
    while( z[0] && (z[0]!='-' || z[1]!='-') ) z++;
    if( z[0] ){
      fprintf(p->out, "\n;\n");
    }else{
      fprintf(p->out, ";\n");
    }
    rc = sqlite3_step(pSelect);
  }
  rc = sqlite3_finalize(pSelect);
  if( rc!=SQLITE_OK ){
    fprintf(p->out, "/**** ERROR: (%d) %s *****/\n", rc, sqlite3_errmsg(p->db));
    p->nErr++;
  }
  return rc;
}
