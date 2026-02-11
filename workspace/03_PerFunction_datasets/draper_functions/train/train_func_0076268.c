bIsEmptyBox(FILE *pFile, const list_mem_type *pAnchor)
{
	const list_mem_type	*pCurr;
	size_t	tIndex, tSize;
	UCHAR	*aucBuffer;
	char	cChar;

	fail(pFile == NULL);

	if (pAnchor == NULL) {
		return TRUE;
	}

	aucBuffer = NULL;
	for (pCurr = pAnchor; pCurr != NULL; pCurr = pCurr->pNext) {
		fail(pCurr->tInfo.ulLength == 0);
		tSize = (size_t)pCurr->tInfo.ulLength;
#if defined(__dos) && !defined(__DJGPP__)
		if (pCurr->tInfo.ulLength > 0xffffUL) {
			tSize = 0xffff;
		}
#endif
		fail(aucBuffer != NULL);
		aucBuffer = xmalloc(tSize);
		if (!bReadBytes(aucBuffer, tSize,
				pCurr->tInfo.ulFileOffset, pFile)) {
			aucBuffer = xfree(aucBuffer);
			return FALSE;
		}
		for (tIndex = 0; tIndex < tSize; tIndex++) {
			cChar = (char)aucBuffer[tIndex];
			switch (cChar) {
			case '\0': case '\r': case '\n':
			case '\f': case '\t': case '\v':
			case ' ':
				break;
			default:
				aucBuffer = xfree(aucBuffer);
				return FALSE;
			}
		}
		aucBuffer = xfree(aucBuffer);
	}
	fail(aucBuffer != NULL);
	return TRUE;
}
