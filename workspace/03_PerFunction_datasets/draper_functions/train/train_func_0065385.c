freePage(Btree *pBt, void *pPage, Pgno pgno){
  PageOne *pPage1 = pBt->page1;
  OverflowPage *pOvfl = (OverflowPage*)pPage;
  int rc;
  int needUnref = 0;
  MemPage *pMemPage;

  if( pgno==0 ){
    assert( pOvfl!=0 );
    pgno = sqlitepager_pagenumber(pOvfl);
  }
  assert( pgno>2 );
  assert( sqlitepager_pagenumber(pOvfl)==pgno );
  pMemPage = (MemPage*)pPage;
  pMemPage->isInit = 0;
  if( pMemPage->pParent ){
    sqlitepager_unref(pMemPage->pParent);
    pMemPage->pParent = 0;
  }
  rc = sqlitepager_write(pPage1);
  if( rc ){
    return rc;
  }
  SWAB_ADD(pBt, pPage1->nFree, 1);
  if( pPage1->nFree!=0 && pPage1->freeList!=0 ){
    OverflowPage *pFreeIdx;
    rc = sqlitepager_get(pBt->pPager, SWAB32(pBt, pPage1->freeList),
                        (void**)&pFreeIdx);
    if( rc==SQLITE_OK ){
      FreelistInfo *pInfo = (FreelistInfo*)pFreeIdx->aPayload;
      int n = SWAB32(pBt, pInfo->nFree);
      if( n<(sizeof(pInfo->aFree)/sizeof(pInfo->aFree[0])) ){
        rc = sqlitepager_write(pFreeIdx);
        if( rc==SQLITE_OK ){
          pInfo->aFree[n] = SWAB32(pBt, pgno);
          SWAB_ADD(pBt, pInfo->nFree, 1);
          sqlitepager_unref(pFreeIdx);
          sqlitepager_dont_write(pBt->pPager, pgno);
          return rc;
        }
      }
      sqlitepager_unref(pFreeIdx);
    }
  }
  if( pOvfl==0 ){
    assert( pgno>0 );
    rc = sqlitepager_get(pBt->pPager, pgno, (void**)&pOvfl);
    if( rc ) return rc;
    needUnref = 1;
  }
  rc = sqlitepager_write(pOvfl);
  if( rc ){
    if( needUnref ) sqlitepager_unref(pOvfl);
    return rc;
  }
  pOvfl->iNext = pPage1->freeList;
  pPage1->freeList = SWAB32(pBt, pgno);
  memset(pOvfl->aPayload, 0, OVERFLOW_SIZE);
  if( needUnref ) rc = sqlitepager_unref(pOvfl);
  return rc;
}
