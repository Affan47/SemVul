lhCursorFirst(unqlite_kv_cursor *pCursor)
{
	lhash_kv_cursor *pCur = (lhash_kv_cursor *)pCursor;
	lhash_kv_engine *pEngine = (lhash_kv_engine *)pCursor->pStore;
	int rc;
	if( pCur->is_first ){

		rc = pEngine->pIo->xGet(pEngine->pIo->pHandle,1,0);
		if( rc != UNQLITE_OK ){
			return rc;
		}
		pCur->is_first = 0;
	}

	pCur->pRec = pEngine->pFirst;

	rc = lhCursorNextPage(pCur);
	return rc;
}
