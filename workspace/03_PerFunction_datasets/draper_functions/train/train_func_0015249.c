vGet0FootnotesInfoAndText(FILE *pFile, const UCHAR *aucHeader)
{
	footnote_local_type	*pCurr;
	UCHAR	*aucBuffer;
	ULONG	ulFileOffset, ulBeginOfText, ulOffset, ulBeginFootnoteInfo;
	ULONG	ulCharPos, ulBeginNextBlock;
	size_t	tFootnotes, tFootnoteInfoLen;
	size_t	tIndex;
	UCHAR   aucTmp[2];

	TRACE_MSG("vGet0FootnotesInfoAndText");

	fail(pFile == NULL || aucHeader == NULL);

	ulBeginOfText = 128;
	NO_DBG_HEX(ulBeginOfText);
	ulBeginFootnoteInfo =  128 * (ULONG)usGetWord(0x14, aucHeader);
	DBG_HEX(ulBeginFootnoteInfo);
	ulBeginNextBlock = 128 * (ULONG)usGetWord(0x16, aucHeader);
	DBG_HEX(ulBeginNextBlock);

	if (ulBeginFootnoteInfo == ulBeginNextBlock) {
		DBG_MSG("No Footnotes in this document");
		return;
	}


	if (!bReadBytes(aucTmp, 2, ulBeginFootnoteInfo, pFile)) {
		return;
	}
	tFootnotes = (size_t)usGetWord(0, aucTmp);
	if (tFootnotes < 2) {
		DBG_MSG("No Footnotes in this document (2)");
	}
	DBG_DEC(tFootnotes);
	tFootnoteInfoLen =  8 * tFootnotes;

	aucBuffer = xmalloc(tFootnoteInfoLen);
	if (!bReadBytes(aucBuffer,
			tFootnoteInfoLen, ulBeginFootnoteInfo + 4, pFile)) {
		aucBuffer = xfree(aucBuffer);
		return;
	}
	DBG_PRINT_BLOCK(aucBuffer, tFootnoteInfoLen);


	fail(tFootnoteListLength != 0);
	tFootnoteListLength = tFootnotes - 1;
	fail(tFootnoteListLength == 0);

	fail(aulFootnoteList != NULL);
	aulFootnoteList = xcalloc(tFootnoteListLength, sizeof(ULONG));

	for (tIndex = 0; tIndex < tFootnoteListLength; tIndex++) {
		ulOffset = ulGetLong(tIndex * 8, aucBuffer);
		DBG_HEX(ulOffset);
		ulFileOffset = ulCharPos2FileOffset(ulBeginOfText + ulOffset);
		DBG_HEX(ulFileOffset);
		aulFootnoteList[tIndex] = ulFileOffset;
	}


	fail(tFootnoteTextLength != 0);
	tFootnoteTextLength = tFootnotes - 1;
	fail(tFootnoteTextLength == 0);

	fail(pFootnoteText != NULL);
	pFootnoteText = xcalloc(tFootnoteTextLength,
				sizeof(footnote_local_type));

	for (tIndex = 0; tIndex < tFootnoteTextLength; tIndex++) {
		pCurr = pFootnoteText + tIndex;
		pCurr->tInfo.szText = NULL;
		ulOffset = ulGetLong(tIndex * 8 + 4, aucBuffer);
		DBG_HEX(ulOffset);
		ulCharPos = ulBeginOfText + ulOffset;
		DBG_HEX(ulCharPos);
		DBG_HEX(ulCharPos2FileOffset(ulCharPos));
		pCurr->ulCharPosStart = ulCharPos;
		ulOffset = ulGetLong((tIndex + 1) * 8 + 4, aucBuffer);
		DBG_HEX(ulOffset);
		ulCharPos = ulBeginOfText + ulOffset;
		DBG_HEX(ulCharPos);
		DBG_HEX(ulCharPos2FileOffset(ulCharPos));
		pCurr->ulCharPosNext = ulCharPos;
		pCurr->bUseful = pCurr->ulCharPosStart != pCurr->ulCharPosNext;
	}
	aucBuffer = xfree(aucBuffer);
}
