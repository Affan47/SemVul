setItem(GR_Item * i)
{
	DELETEP(m_pItem);
	m_pItem =i;
	if(m_pRenderInfo)
	{
		m_pRenderInfo->m_pItem = m_pItem;
	}
}
