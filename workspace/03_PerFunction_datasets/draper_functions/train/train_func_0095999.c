sqlite_create_aggregate(
  sqlite *db,
  const char *zName,
  int nArg,
  void (*xStep)(sqlite_func*,int,const char**),
  void (*xFinalize)(sqlite_func*),
  void *pUserData
){
  FuncDef *p;
  int nName;
  if( db==0 || zName==0 || sqliteSafetyCheck(db) ) return 1;
  if( nArg<-1 || nArg>127 ) return 1;
  nName = strlen(zName);
  if( nName>255 ) return 1;
  p = sqliteFindFunction(db, zName, nName, nArg, 1);
  if( p==0 ) return 1;
  p->xFunc = 0;
  p->xStep = xStep;
  p->xFinalize = xFinalize;
  p->pUserData = pUserData;
  return 0;
}
