_findFormatItem(const char* format)
{
	UT_uint32 iCount = m_vecData.getItemCount();

	for (UT_uint32 i=0; i<iCount; i++)
	{
		_ClipboardItem* pItem = (_ClipboardItem*) m_vecData.getNthItem(i);
		if (g_ascii_strcasecmp(format, pItem->m_szFormat) == 0)
			return pItem;
	}

	return NULL;
}
