sqliteFindIndex(sqlite *db, const char *zName, const char *zDb){
  Index *p = 0;
  int i;
  for(i=0; i<db->nDb; i++){
    int j = (i<2) ? i^1 : i;
    if( zDb && sqliteStrICmp(zDb, db->aDb[j].zName) ) continue;
    p = sqliteHashFind(&db->aDb[j].idxHash, zName, strlen(zName)+1);
    if( p ) break;
  }
  return p;
}
