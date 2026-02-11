printTableStart(
	const char*		pszTitle,
	FLMUINT			uiColumns,
	FLMUINT			uiWidthFactor)
{
	fnPrintf( m_pHRequest, "<table border=0 cellpadding=2 cellspacing=0");
	if (uiWidthFactor)
	{
		fnPrintf( m_pHRequest, " width=%u%%", (unsigned) uiWidthFactor);
	}

	fnPrintf( m_pHRequest, ">\n");

	if (pszTitle)
	{
		printTableRowStart();
		fnPrintf( m_pHRequest, "<td colspan=%u class=\"tablehead1\"",
					(unsigned) uiColumns);
		fnPrintf( m_pHRequest, ">\n");
		printEncodedString( pszTitle);
		fnPrintf( m_pHRequest, "</td>");
		printTableRowEnd();
	}
}
