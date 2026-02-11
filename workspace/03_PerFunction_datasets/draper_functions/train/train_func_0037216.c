unqlite_kv_delete(unqlite *pDb,const void *pKey,int nKeyLen)
{
	unqlite_kv_methods *pMethods;
	unqlite_kv_engine *pEngine;
	unqlite_kv_cursor *pCur;
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
	 pMethods = pEngine->pIo->pMethods;
	 pCur = pDb->sDB.pCursor;
	 if( pMethods->xDelete == 0 ){

		 unqliteGenError(pDb,"xDelete() method not implemented in the underlying storage engine");
		 rc = UNQLITE_NOTIMPLEMENTED;
	 }else{
		 if( nKeyLen < 0 ){

			 nKeyLen = SyStrlen((const char *)pKey);
		 }
		 if( !nKeyLen ){
			 unqliteGenError(pDb,"Empty key");
			 rc = UNQLITE_EMPTY;
		 }else{

			 rc = pMethods->xSeek(pCur,pKey,nKeyLen,UNQLITE_CURSOR_MATCH_EXACT);
		 }
		 if( rc == UNQLITE_OK ){

			 rc = pMethods->xDelete(pCur);
		 }
	 }
#if defined(UNQLITE_ENABLE_THREADS)

	 SyMutexLeave(sUnqlMPGlobal.pMutexMethods,pDb->pMutex);
#endif
	return rc;
}
