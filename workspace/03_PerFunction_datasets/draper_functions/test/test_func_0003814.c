vGet2FootnotesText(FILE *pFile, const UCHAR *aucHeader)
{
	footnote_local_type	*pCurr;
	UCHAR	*aucBuffer;
	ULONG	ulCharPos, ulBeginOfFootnotes, ulOffset, ulBeginFootnoteText;
	size_t	tFootnoteTextLen;
	size_t	tIndex;

	TRACE_MSG("vGet2FootnotesText");

	fail(pFile == NULL || aucHeader == NULL);

	ulBeginOfFootnotes = ulGetLong(0x18, aucHeader);
	ulBeginOfFootnotes += ulGetLong(0x34, aucHeader);
	NO_DBG_HEX(ulBeginOfFootnotes);

	ulBeginFootnoteText = ulGetLong(0x6a, aucHeader);
	NO_DBG_HEX(ulBeginFootnoteText);
	tFootnoteTextLen =
		(size_t)usGetWord(0x6e, aucHeader);
	NO_DBG_DEC(tFootnoteTextLen);

	if (tFootnoteTextLen < 12) {
		DBG_MSG("No Footnote text in this document");
		return;
	}

	aucBuffer = xmalloc(tFootnoteTextLen);
	if (!bReadBytes(aucBuffer,
			tFootnoteTextLen, ulBeginFootnoteText, pFile)) {
		aucBuffer = xfree(aucBuffer);
		return;
	}
	NO_DBG_PRINT_BLOCK(aucBuffer, tFootnoteTextLen);

	fail(tFootnoteTextLength != 0);
	tFootnoteTextLength = tFootnoteTextLen / 4 - 2;
	fail(tFootnoteTextLength == 0);

	fail(pFootnoteText != NULL);
	pFootnoteText = xcalloc(tFootnoteTextLength,
				sizeof(footnote_local_type));

	for (tIndex = 0; tIndex < tFootnoteTextLength; tIndex++) {
		pCurr = pFootnoteText + tIndex;
		pCurr->tInfo.szText = NULL;
		ulOffset = ulGetLong(tIndex * 4, aucBuffer);
		NO_DBG_HEX(ulOffset);
		ulCharPos = ulBeginOfFootnotes + ulOffset;
		NO_DBG_HEX(ulCharPos);
		NO_DBG_HEX(ulCharPos2FileOffset(ulCharPos));
		pCurr->ulCharPosStart = ulCharPos;
		ulOffset = ulGetLong(tIndex * 4 + 4, aucBuffer);
		NO_DBG_HEX(ulOffset);
		ulCharPos = ulBeginOfFootnotes + ulOffset;
		NO_DBG_HEX(ulCharPos);
		NO_DBG_HEX(ulCharPos2FileOffset(ulCharPos));
		pCurr->ulCharPosNext = ulCharPos;
		pCurr->bUseful = pCurr->ulCharPosStart != pCurr->ulCharPosNext;
	}
	aucBuffer = xfree(aucBuffer);
}
