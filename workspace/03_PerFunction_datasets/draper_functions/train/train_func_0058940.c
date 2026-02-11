tSkipToData(FILE *pFile, size_t tMaxBytes, size_t *ptSkipped)
{
	ULONG	ulName, ulTmp;
	size_t	tDataLength, tToSkip;
	int	iCounter;

	fail(pFile == NULL);
	fail(ptSkipped == NULL);


	while (*ptSkipped + 8 < tMaxBytes) {
		tDataLength = (size_t)ulNextLongBE(pFile);
		DBG_DEC(tDataLength);
		*ptSkipped += 4;

		ulName = 0x00;
		for (iCounter = 0; iCounter < 4; iCounter++) {
			ulTmp = (ULONG)iNextByte(pFile);
			if (!isalpha((int)ulTmp)) {
				DBG_HEX(ulTmp);
				return (size_t)-1;
			}
			ulName <<= 8;
			ulName |= ulTmp;
		}
		DBG_HEX(ulName);
		*ptSkipped += 4;

		if (ulName == PNG_CN_IEND) {
			break;
		}
		if (ulName == PNG_CN_IDAT) {
			return tDataLength;
		}

		tToSkip = tDataLength + 4;
		if (tToSkip >= tMaxBytes - *ptSkipped) {
			DBG_DEC(tToSkip);
			DBG_DEC(tMaxBytes - *ptSkipped);
			return (size_t)-1;
		}
		(void)tSkipBytes(pFile, tToSkip);
		*ptSkipped += tToSkip;
	}

	return (size_t)-1;
}
