lhCursorData(unqlite_kv_cursor *pCursor,int (*xConsumer)(const void *,unsigned int,void *),void *pUserData)
{
	lhash_kv_cursor *pCur = (lhash_kv_cursor *)pCursor;
	lhcell *pCell;
	int rc;
	if( pCur->iState != L_HASH_CURSOR_STATE_CELL || pCur->pCell == 0 ){

		return UNQLITE_INVALID;
	}

	pCell = pCur->pCell;

	rc = lhConsumeCellData(pCell,xConsumer,pUserData);
	return rc;
}
