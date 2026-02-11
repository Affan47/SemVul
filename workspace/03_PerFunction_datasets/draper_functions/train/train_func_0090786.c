setLayoutItem(UT_uint32 indexLayoutItem, XAP_Toolbar_Id id, EV_Toolbar_LayoutFlags flags)
{
	UT_ASSERT(indexLayoutItem < m_nrLayoutItems);
	DELETEP(m_layoutTable[indexLayoutItem]);
	m_layoutTable[indexLayoutItem] = new EV_Toolbar_LayoutItem(id,flags);
	return (m_layoutTable[indexLayoutItem] != NULL);
}
