vSubstringXML(diagram_type *pDiag,
	const char *szString, size_t tStringLength, long lStringWidth,
	USHORT usFontstyle)
{
	fail(pDiag == NULL || szString == NULL);
	fail(pDiag->pOutFile == NULL);
	fail(pDiag->lXleft < 0);
	fail(tStringLength != strlen(szString));

	if (szString[0] == '\0' || tStringLength == 0) {
		return;
	}

	vPrintXML(pDiag, szString, tStringLength, usFontstyle);
	pDiag->lXleft += lStringWidth;
}
