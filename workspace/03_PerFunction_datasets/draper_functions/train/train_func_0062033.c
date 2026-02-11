unqliteDbRelease(unqlite *pDb)
{
	unqlite_db *pStore = &pDb->sDB;
	unqlite_vm *pVm,*pNext;
	int rc = UNQLITE_OK;
	if( (pDb->iFlags & UNQLITE_FL_DISABLE_AUTO_COMMIT) == 0 ){

		rc = unqlitePagerCommit(pStore->pPager);
		if( rc != UNQLITE_OK ){

			rc = unqlitePagerRollback(pStore->pPager,FALSE);
		}
	}else{

		rc = unqlitePagerRollback(pStore->pPager,FALSE);
	}

	unqlitePagerClose(pStore->pPager);
#ifndef DISABLE_JX9

	pVm = pDb->pVms;
	for(;;){
		if( pDb->iVm < 1 ){
			break;
		}

		pNext = pVm->pNext;
		unqliteVmRelease(pVm);
		pVm = pNext;
		pDb->iVm--;
	}

	jx9_release(pStore->pJx9);
#endif

	pDb->nMagic = 0x7250;

	SyMemBackendRelease(&pDb->sMem);

	return rc;
}
