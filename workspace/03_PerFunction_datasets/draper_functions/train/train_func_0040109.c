bGet6DocumentText(FILE *pFile, BOOL bUsesUnicode, ULONG ulStartBlock,
	const ULONG *aulBBD, size_t tBBDLen, const UCHAR *aucHeader)
{
	UCHAR	*aucBuffer;
	ULONG	ulBeginTextInfo, ulTextOffset, ulTotLength;
	size_t	tTextInfoLen;
	int	iIndex, iType, iOff, iLen, iPieces;
	USHORT	usPropMod;

	DBG_MSG("bGet6DocumentText");

	fail(pFile == NULL);
	fail(aulBBD == NULL);
	fail(aucHeader == NULL);

	ulBeginTextInfo = ulGetLong(0x160, aucHeader);
	DBG_HEX(ulBeginTextInfo);
	tTextInfoLen = (size_t)ulGetLong(0x164, aucHeader);
	DBG_DEC(tTextInfoLen);

	aucBuffer = xmalloc(tTextInfoLen);
	if (!bReadBuffer(pFile, ulStartBlock,
			aulBBD, tBBDLen, BIG_BLOCK_SIZE,
			aucBuffer, ulBeginTextInfo, tTextInfoLen)) {
		aucBuffer = xfree(aucBuffer);
		return FALSE;
	}
	NO_DBG_PRINT_BLOCK(aucBuffer, tTextInfoLen);

	iOff = 0;
	while ((size_t)iOff < tTextInfoLen) {
		iType = (int)ucGetByte(iOff, aucBuffer);
		iOff++;
		if (iType == 0) {
			DBG_FIXME();
			iOff++;
			continue;
		}
		if (iType == 1) {
			iLen = (int)usGetWord(iOff, aucBuffer);
			vAdd2PropModList(aucBuffer + iOff);
			iOff += iLen + 2;
			continue;
		}
		if (iType != 2) {
			werr(0, "Unknown type of 'fastsaved' format");
			aucBuffer = xfree(aucBuffer);
			return FALSE;
		}

		iLen = (int)usGetWord(iOff, aucBuffer);
		NO_DBG_DEC(iLen);
		iOff += 4;
		iPieces = (iLen - 4) / 12;
		DBG_DEC(iPieces);
		for (iIndex = 0; iIndex < iPieces; iIndex++) {
			ulTextOffset = ulGetLong(
				iOff + (iPieces + 1) * 4 + iIndex * 8 + 2,
				aucBuffer);
			usPropMod = usGetWord(
				iOff + (iPieces + 1) * 4 + iIndex * 8 + 6,
				aucBuffer);
			ulTotLength = ulGetLong(iOff + (iIndex + 1) * 4,
						aucBuffer) -
					ulGetLong(iOff + iIndex * 4,
						aucBuffer);
			NO_DBG_HEX_C(usPropMod != 0, usPropMod);
			if (!bAddTextBlocks(ulTextOffset, ulTotLength,
					bUsesUnicode, usPropMod,
					ulStartBlock,
					aulBBD, tBBDLen)) {
				aucBuffer = xfree(aucBuffer);
				return FALSE;
			}
		}
		break;
	}
	aucBuffer = xfree(aucBuffer);
	return TRUE;
}
