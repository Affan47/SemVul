fileBtreeRollback(Btree *pBt){
  int rc;
  BtCursor *pCur;
  if( pBt->inTrans==0 ) return SQLITE_OK;
  pBt->inTrans = 0;
  pBt->inCkpt = 0;
  rc = pBt->readOnly ? SQLITE_OK : sqlitepager_rollback(pBt->pPager);
  for(pCur=pBt->pCursor; pCur; pCur=pCur->pNext){
    if( pCur->pPage && pCur->pPage->isInit==0 ){
      sqlitepager_unref(pCur->pPage);
      pCur->pPage = 0;
    }
  }
  unlockBtreeIfUnused(pBt);
  return rc;
}
