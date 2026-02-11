fileBtreeMoveto(BtCursor *pCur, const void *pKey, int nKey, int *pRes){
  int rc;
  if( pCur->pPage==0 ) return SQLITE_ABORT;
  pCur->eSkip = SKIP_NONE;
  rc = moveToRoot(pCur);
  if( rc ) return rc;
  for(;;){
    int lwr, upr;
    Pgno chldPg;
    MemPage *pPage = pCur->pPage;
    int c = -1;
    lwr = 0;
    upr = pPage->nCell-1;
    while( lwr<=upr ){
      pCur->idx = (lwr+upr)/2;
      rc = fileBtreeKeyCompare(pCur, pKey, nKey, 0, &c);
      if( rc ) return rc;
      if( c==0 ){
        pCur->iMatch = c;
        if( pRes ) *pRes = 0;
        return SQLITE_OK;
      }
      if( c<0 ){
        lwr = pCur->idx+1;
      }else{
        upr = pCur->idx-1;
      }
    }
    assert( lwr==upr+1 );
    assert( pPage->isInit );
    if( lwr>=pPage->nCell ){
      chldPg = pPage->u.hdr.rightChild;
    }else{
      chldPg = pPage->apCell[lwr]->h.leftChild;
    }
    if( chldPg==0 ){
      pCur->iMatch = c;
      if( pRes ) *pRes = c;
      return SQLITE_OK;
    }
    pCur->idx = lwr;
    rc = moveToChild(pCur, chldPg);
    if( rc ) return rc;
  }

}
