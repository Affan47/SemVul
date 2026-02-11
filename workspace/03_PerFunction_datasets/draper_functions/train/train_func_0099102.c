unqlite_kv_store_fmt(unqlite *pDb,const void *pKey,int nKeyLen,const char *zFormat,...)
{
	unqlite_kv_engine *pEngine;
	int rc;
	if( UNQLITE_DB_MISUSE(pDb) ){
		return UNQLITE_CORRUPT;
	}
#if defined(UNQLITE_ENABLE_THREADS)

	 SyMutexEnter(sUnqlMPGlobal.pMutexMethods, pDb->pMutex);
	 if( sUnqlMPGlobal.nThreadingLevel > UNQLITE_THREAD_LEVEL_SINGLE &&
		 UNQLITE_THRD_DB_RELEASE(pDb) ){
			 return UNQLITE_ABORT;
	 }
#endif

	 pEngine = unqlitePagerGetKvEngine(pDb);
	 if( pEngine->pIo->pMethods->xReplace == 0 ){

		 unqliteGenError(pDb,"xReplace() method not implemented in the underlying storage engine");
		 rc = UNQLITE_NOTIMPLEMENTED;
	 }else{
		 if( nKeyLen < 0 ){

			 nKeyLen = SyStrlen((const char *)pKey);
		 }
		 if( !nKeyLen ){
			 unqliteGenError(pDb,"Empty key");
			 rc = UNQLITE_EMPTY;
		 }else{
			 SyBlob sWorker;
			 va_list ap;
			 SyBlobInit(&sWorker,&pDb->sMem);

			 va_start(ap,zFormat);
			 SyBlobFormatAp(&sWorker,zFormat,ap);
			 va_end(ap);

			 rc = pEngine->pIo->pMethods->xReplace(pEngine,pKey,nKeyLen,SyBlobData(&sWorker),SyBlobLength(&sWorker));

			 SyBlobRelease(&sWorker);
		 }
	 }
#if defined(UNQLITE_ENABLE_THREADS)

	 SyMutexLeave(sUnqlMPGlobal.pMutexMethods,pDb->pMutex);
#endif
	return rc;
}
