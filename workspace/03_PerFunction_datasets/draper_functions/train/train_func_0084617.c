SyBlobAppend(SyBlob *pBlob, const void *pData, sxu32 nSize)
{
	sxu8 *zBlob;
	sxi32 rc;
	if( nSize < 1 ){
		return SXRET_OK;
	}
	rc = BlobPrepareGrow(&(*pBlob), &nSize);
	if( SXRET_OK != rc ){
		return rc;
	}
	if( pData ){
		zBlob = (sxu8 *)pBlob->pBlob ;
		zBlob = &zBlob[pBlob->nByte];
		pBlob->nByte += nSize;
		SX_MACRO_FAST_MEMCPY(pData, zBlob, nSize);
	}
	return SXRET_OK;
}
