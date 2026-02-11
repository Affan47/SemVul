pager_get_all_dirty_pages(Pager *pPager){
  PgHdr *p, *pList;
  pList = 0;
  for(p=pPager->pAll; p; p=p->pNextAll){
    if( p->dirty ){
      p->pDirty = pList;
      pList = p;
    }
  }
  return pList;
}
