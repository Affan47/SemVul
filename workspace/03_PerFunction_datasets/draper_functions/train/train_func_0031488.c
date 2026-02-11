usGetNextByte(FILE *pFile, readinfo_type *pInfoCurrent, list_mem_type *pAnchor,
	ULONG *pulFileOffset, ULONG *pulCharPos, USHORT *pusPropMod)
{
	ULONG	ulReadOff;
	size_t	tReadLen;

	fail(pInfoCurrent == NULL);

	if (pInfoCurrent->pBlockCurrent == NULL ||
	    pInfoCurrent->tByteNext >= sizeof(pInfoCurrent->aucBlock) ||
	    pInfoCurrent->ulBlockOffset + pInfoCurrent->tByteNext >=
				pInfoCurrent->pBlockCurrent->tInfo.ulLength) {
		if (pInfoCurrent->pBlockCurrent == NULL) {

			pInfoCurrent->pBlockCurrent = pAnchor;
			pInfoCurrent->ulBlockOffset = 0;
		} else if (pInfoCurrent->ulBlockOffset +
				sizeof(pInfoCurrent->aucBlock) <
				pInfoCurrent->pBlockCurrent->tInfo.ulLength) {

			pInfoCurrent->ulBlockOffset +=
					sizeof(pInfoCurrent->aucBlock);
		} else {

			pInfoCurrent->pBlockCurrent =
					pInfoCurrent->pBlockCurrent->pNext;
			pInfoCurrent->ulBlockOffset = 0;
		}
		if (pInfoCurrent->pBlockCurrent == NULL) {

			return (USHORT)EOF;
		}
		tReadLen = (size_t)
			(pInfoCurrent->pBlockCurrent->tInfo.ulLength -
			 pInfoCurrent->ulBlockOffset);
		if (tReadLen > sizeof(pInfoCurrent->aucBlock)) {
			tReadLen = sizeof(pInfoCurrent->aucBlock);
		}
		ulReadOff = pInfoCurrent->pBlockCurrent->tInfo.ulFileOffset +
				pInfoCurrent->ulBlockOffset;
		if (!bReadBytes(pInfoCurrent->aucBlock,
						tReadLen, ulReadOff, pFile)) {

			pInfoCurrent->pBlockCurrent = NULL;
			return (USHORT)EOF;
		}
		pInfoCurrent->tByteNext = 0;
	}
	if (pulFileOffset != NULL) {
		*pulFileOffset =
			pInfoCurrent->pBlockCurrent->tInfo.ulFileOffset +
			pInfoCurrent->ulBlockOffset +
			pInfoCurrent->tByteNext;
	}
	if (pulCharPos != NULL) {
		*pulCharPos =
			pInfoCurrent->pBlockCurrent->tInfo.ulCharPos +
			pInfoCurrent->ulBlockOffset +
			pInfoCurrent->tByteNext;
	}
	if (pusPropMod != NULL) {
		*pusPropMod = pInfoCurrent->pBlockCurrent->tInfo.usPropMod;
	}
	return (USHORT)pInfoCurrent->aucBlock[pInfoCurrent->tByteNext++];
}
