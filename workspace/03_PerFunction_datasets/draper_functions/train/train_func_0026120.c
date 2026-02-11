moveToRoot(BtCursor *pCur){
  MemPage *pNew;
  int rc;
  Btree *pBt = pCur->pBt;

  rc = sqlitepager_get(pBt->pPager, pCur->pgnoRoot, (void**)&pNew);
  if( rc ) return rc;
  rc = initPage(pBt, pNew, pCur->pgnoRoot, 0);
  if( rc ) return rc;
  sqlitepager_unref(pCur->pPage);
  pCur->pPage = pNew;
  pCur->idx = 0;
  return SQLITE_OK;
}
