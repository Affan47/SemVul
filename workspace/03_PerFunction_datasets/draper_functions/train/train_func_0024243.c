getLayoutIndex(XAP_Menu_Id id) const
{
	UT_sint32 size_table = m_layoutTable.size();
	UT_sint32 index;

	for (index = 0; index < size_table; ++index)
	{
		if ((m_layoutTable[index])->getMenuId() == id) {
			break;
		}
	}

	return ((index < size_table) ? index : 0);
}
