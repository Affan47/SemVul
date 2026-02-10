sqliteBeginParse(Parse *pParse, int explainFlag){
  sqlite *db = pParse->db;
  int i;
  pParse->explain = explainFlag;
  if((db->flags & SQLITE_Initialized)==0 && db->init.busy==0 ){
    int rc = sqliteInit(db, &pParse->zErrMsg);
    if( rc!=SQLITE_OK ){
      pParse->rc = rc;
      pParse->nErr++;
    }
  }
  for(i=0; i<db->nDb; i++){
    DbClearProperty(db, i, DB_Locked);
    if( !db->aDb[i].inTrans ){
      DbClearProperty(db, i, DB_Cookie);
    }
  }
  pParse->nVar = 0;
}
