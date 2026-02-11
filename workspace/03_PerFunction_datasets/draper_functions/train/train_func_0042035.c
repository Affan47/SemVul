_page_ref(PgHdr *pPg){
  if( pPg->nRef==0 ){

    if( pPg==pPg->pPager->pFirstSynced ){
      PgHdr *p = pPg->pNextFree;
      while( p && p->needSync ){ p = p->pNextFree; }
      pPg->pPager->pFirstSynced = p;
    }
    if( pPg->pPrevFree ){
      pPg->pPrevFree->pNextFree = pPg->pNextFree;
    }else{
      pPg->pPager->pFirst = pPg->pNextFree;
    }
    if( pPg->pNextFree ){
      pPg->pNextFree->pPrevFree = pPg->pPrevFree;
    }else{
      pPg->pPager->pLast = pPg->pPrevFree;
    }
    pPg->pPager->nRef++;
  }
  pPg->nRef++;
  REFINFO(pPg);
}
