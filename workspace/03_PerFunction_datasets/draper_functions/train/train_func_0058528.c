SyMemBackendInitFromParent(SyMemBackend *pBackend,const SyMemBackend *pParent)
{
	sxu8 bInheritMutex;
#if defined(UNTRUST)
	if( pBackend == 0 || SXMEM_BACKEND_CORRUPT(pParent) ){
		return SXERR_CORRUPT;
	}
#endif

	SyZero(&(*pBackend), sizeof(SyMemBackend));
	pBackend->pMethods  = pParent->pMethods;
	pBackend->xMemError = pParent->xMemError;
	pBackend->pUserData = pParent->pUserData;
	bInheritMutex = pParent->pMutexMethods ? TRUE : FALSE;
	if( bInheritMutex ){
		pBackend->pMutexMethods = pParent->pMutexMethods;

		pBackend->pMutex = pBackend->pMutexMethods->xNew(SXMUTEX_TYPE_FAST);
		if( pBackend->pMutex ==  0){
			return SXERR_OS;
		}
	}
#if defined(UNTRUST)
	pBackend->nMagic = SXMEM_BACKEND_MAGIC;
#endif
	return SXRET_OK;
}
