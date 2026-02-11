CountRulePreContexts()
{
	m_critOriginal = m_vprit.size();

	m_critPreModContext = 0;
	for (size_t irit = 0; irit < m_vprit.size(); irit++)
	{
		if (dynamic_cast<GdlSetAttrItem *>(m_vprit[irit]))
			return m_critPreModContext;
		m_critPreModContext++;
	}


	Assert(false);
	return m_critPreModContext;
}
