_getTabDimensionString(UT_sint32 tabIndex)
{

	UT_return_val_if_fail (tabIndex < m_tabInfo.getItemCount(), NULL);

	fl_TabStop *pTabInfo = m_tabInfo.getNthItem(tabIndex);

	const char* pStart = &m_pszTabStops[pTabInfo->getOffset()];
	const char* pEnd = pStart;
	while (*pEnd && (*pEnd != '/'))
	{
		pEnd++;
	}

	UT_uint32 iLen = pEnd - pStart;
	UT_return_val_if_fail (iLen<20, NULL);

	strncpy(buf, pStart, iLen);
	buf[iLen]=0;

	return buf;
}
