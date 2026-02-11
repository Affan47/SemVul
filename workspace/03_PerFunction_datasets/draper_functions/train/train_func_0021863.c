clearClipboard(void)
{
	UT_sint32 iCount = m_vecData.getItemCount();
	for (int i=0; i<iCount; i++)
	{
		_ClipboardItem* pItem = (_ClipboardItem*) m_vecData.getNthItem(i);
		DELETEP(pItem);
	}

	m_vecData.clear();

	return true;
}
