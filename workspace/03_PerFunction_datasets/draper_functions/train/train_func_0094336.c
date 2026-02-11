fileBtreeCloseCursor(BtCursor *pCur){
  Btree *pBt = pCur->pBt;
  if( pCur->pPrev ){
    pCur->pPrev->pNext = pCur->pNext;
  }else{
    pBt->pCursor = pCur->pNext;
  }
  if( pCur->pNext ){
    pCur->pNext->pPrev = pCur->pPrev;
  }
  if( pCur->pPage ){
    sqlitepager_unref(pCur->pPage);
  }
  if( pCur->pShared!=pCur ){
    BtCursor *pRing = pCur->pShared;
    while( pRing->pShared!=pCur ){ pRing = pRing->pShared; }
    pRing->pShared = pCur->pShared;
  }
  unlockBtreeIfUnused(pBt);
  sqliteFree(pCur);
  return SQLITE_OK;
}
