page_unref(Page *pPage)
{
	pPage->nRef--;
	if( pPage->nRef < 1	){
		Pager *pPager = pPage->pPager;
		if( !(pPage->flags & PAGE_DIRTY)  ){
			pager_unlink_page(pPager,pPage);

			pager_release_page(pPager,pPage);
		}else{
			if( pPage->flags & PAGE_DONT_MAKE_HOT ){

				return;
			}
			if( !(pPage->flags & PAGE_HOT_DIRTY) ){

				pPage->pPrevHot = 0;
				if( pPager->pFirstHot == 0 ){
					pPager->pFirstHot = pPager->pHotDirty = pPage;
				}else{
					pPage->pNextHot = pPager->pHotDirty;
					if( pPager->pHotDirty ){
						pPager->pHotDirty->pPrevHot = pPage;
					}
					pPager->pHotDirty = pPage;
				}
				pPager->nHot++;
				pPage->flags |= PAGE_HOT_DIRTY;
			}
		}
	}
}
