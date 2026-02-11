sqliteDropTrigger(Parse *pParse, SrcList *pName){
  Trigger *pTrigger;
  int i;
  const char *zDb;
  const char *zName;
  int nName;
  sqlite *db = pParse->db;

  if( sqlite_malloc_failed ) goto drop_trigger_cleanup;
  assert( pName->nSrc==1 );
  zDb = pName->a[0].zDatabase;
  zName = pName->a[0].zName;
  nName = strlen(zName);
  for(i=0; i<db->nDb; i++){
    int j = (i<2) ? i^1 : i;
    if( zDb && sqliteStrICmp(db->aDb[j].zName, zDb) ) continue;
    pTrigger = sqliteHashFind(&(db->aDb[j].trigHash), zName, nName+1);
    if( pTrigger ) break;
  }
  if( !pTrigger ){
    sqliteErrorMsg(pParse, "no such trigger: %S", pName, 0);
    goto drop_trigger_cleanup;
  }
  sqliteDropTriggerPtr(pParse, pTrigger, 0);

drop_trigger_cleanup:
  sqliteSrcListDelete(pName);
}
