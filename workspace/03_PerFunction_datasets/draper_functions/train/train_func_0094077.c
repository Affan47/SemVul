sqliteAddIdxKeyType(Vdbe *v, Index *pIdx){
  char *zType;
  Table *pTab;
  int i, n;
  assert( pIdx!=0 && pIdx->pTable!=0 );
  pTab = pIdx->pTable;
  n = pIdx->nColumn;
  zType = sqliteMallocRaw( n+1 );
  if( zType==0 ) return;
  for(i=0; i<n; i++){
    int iCol = pIdx->aiColumn[i];
    assert( iCol>=0 && iCol<pTab->nCol );
    if( (pTab->aCol[iCol].sortOrder & SQLITE_SO_TYPEMASK)==SQLITE_SO_TEXT ){
      zType[i] = 't';
    }else{
      zType[i] = 'n';
    }
  }
  zType[n] = 0;
  sqliteVdbeChangeP3(v, -1, zType, n);
  sqliteFree(zType);
}
