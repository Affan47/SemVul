sqliteFindFunction(
  sqlite *db,
  const char *zName,
  int nName,
  int nArg,
  int createFlag
){
  FuncDef *pFirst, *p, *pMaybe;
  pFirst = p = (FuncDef*)sqliteHashFind(&db->aFunc, zName, nName);
  if( p && !createFlag && nArg<0 ){
    while( p && p->xFunc==0 && p->xStep==0 ){ p = p->pNext; }
    return p;
  }
  pMaybe = 0;
  while( p && p->nArg!=nArg ){
    if( p->nArg<0 && !createFlag && (p->xFunc || p->xStep) ) pMaybe = p;
    p = p->pNext;
  }
  if( p && !createFlag && p->xFunc==0 && p->xStep==0 ){
    return 0;
  }
  if( p==0 && pMaybe ){
    assert( createFlag==0 );
    return pMaybe;
  }
  if( p==0 && createFlag && (p = sqliteMalloc(sizeof(*p)))!=0 ){
    p->nArg = nArg;
    p->pNext = pFirst;
    p->dataType = pFirst ? pFirst->dataType : SQLITE_NUMERIC;
    sqliteHashInsert(&db->aFunc, zName, nName, (void*)p);
  }
  return p;
}
