bAddDataBlocks(ULONG ulDataPosFirst, ULONG ulTotalLength,
	ULONG ulStartBlock, const ULONG *aulBBD, size_t tBBDLen)
{
	data_block_type	tDataBlock;
	ULONG	ulDataPos, ulOffset, ulIndex;
	long	lToGo;
	BOOL	bSuccess;

	fail(ulTotalLength > (ULONG)LONG_MAX);
	fail(ulStartBlock > MAX_BLOCKNUMBER && ulStartBlock != END_OF_CHAIN);
	fail(aulBBD == NULL);

	NO_DBG_HEX(ulDataPosFirst);
	NO_DBG_DEC(ulTotalLength);

	lToGo = (long)ulTotalLength;

	ulDataPos = ulDataPosFirst;
	ulOffset = ulDataPosFirst;
	for (ulIndex = ulStartBlock;
	     ulIndex != END_OF_CHAIN && lToGo > 0;
	     ulIndex = aulBBD[ulIndex]) {
		if (ulIndex == UNUSED_BLOCK || ulIndex >= (ULONG)tBBDLen) {
			DBG_DEC(ulIndex);
			DBG_DEC(tBBDLen);
			return FALSE;
		}
		if (ulOffset >= BIG_BLOCK_SIZE) {
			ulOffset -= BIG_BLOCK_SIZE;
			continue;
		}
		tDataBlock.ulFileOffset =
			(ulIndex + 1) * BIG_BLOCK_SIZE + ulOffset;
		tDataBlock.ulDataPos = ulDataPos;
		tDataBlock.ulLength = min(BIG_BLOCK_SIZE - ulOffset,
						(ULONG)lToGo);
		fail(tDataBlock.ulLength > BIG_BLOCK_SIZE);
		ulOffset = 0;
		if (!bAdd2DataBlockList(&tDataBlock)) {
			DBG_HEX(tDataBlock.ulFileOffset);
			DBG_HEX(tDataBlock.ulDataPos);
			DBG_DEC(tDataBlock.ulLength);
			return FALSE;
		}
		ulDataPos += tDataBlock.ulLength;
		lToGo -= (long)tDataBlock.ulLength;
	}
	bSuccess = lToGo == 0 ||
		(ulTotalLength == (ULONG)LONG_MAX && ulIndex == END_OF_CHAIN);
	DBG_DEC_C(!bSuccess, lToGo);
	DBG_DEC_C(!bSuccess, ulTotalLength);
	DBG_DEC_C(!bSuccess, ulIndex);
	return bSuccess;
}
