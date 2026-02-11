lhRestoreSpace(lhpage *pPage,sxu16 iOfft,sxu16 nByte)
{
	unsigned char *zRaw;
	if( nByte < 4 ){

		return UNQLITE_OK;
	}

	zRaw = &pPage->pRaw->zData[iOfft];

	SyBigEndianPack16(zRaw,pPage->sHdr.iFree);
	zRaw += 2;
	SyBigEndianPack16(zRaw,nByte);

	SyBigEndianPack16(&pPage->pRaw->zData[2],iOfft);
	pPage->sHdr.iFree = iOfft;
	pPage->nFree += nByte;
	return UNQLITE_OK;
}
