lhCellWriteLocalPayload(lhcell *pCell,
	const void *pKey,sxu32 nKeylen,
	const void *pData,unqlite_int64 nDatalen
	)
{

	lhpage *pPage = pCell->pPage;
	unsigned char *zRaw = pPage->pRaw->zData;

	zRaw += pCell->iStart + L_HASH_CELL_SZ;

	SyMemcpy(pKey,(void *)zRaw,nKeylen);
	zRaw += nKeylen;
	if( nDatalen > 0 ){

		SyMemcpy(pData,(void *)zRaw,(sxu32)nDatalen);
	}
	return UNQLITE_OK;
}
