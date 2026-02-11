sqliteIsReadOnly(Parse *pParse, Table *pTab, int viewOk){
  if( pTab->readOnly ){
    sqliteErrorMsg(pParse, "table %s may not be modified", pTab->zName);
    return 1;
  }
  if( !viewOk && pTab->pSelect ){
    sqliteErrorMsg(pParse, "cannot modify %s because it is a view",pTab->zName);
    return 1;
  }
  return 0;
}
