pager_get_page_contents(Pager *pPager,Page *pPage,int noContent)
{
	int rc = UNQLITE_OK;
	if( pPager->is_mem || noContent || pPage->pgno >= pPager->dbSize ){

		SyZero(pPage->zData,pPager->iPageSize);
		return UNQLITE_OK;
	}
	if( (pPager->iOpenFlags & UNQLITE_OPEN_MMAP) && (pPager->pMmap ) ){
		unsigned char *zMap = (unsigned char *)pPager->pMmap;
		pPage->zData = &zMap[pPage->pgno * pPager->iPageSize];
	}else{

		rc = unqliteOsRead(pPager->pfd,pPage->zData,pPager->iPageSize,pPage->pgno * pPager->iPageSize);
	}
	return rc;
}
