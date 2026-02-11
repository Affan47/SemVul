SortKey()
{

	int critIns = 0;
	for (size_t irit = 0; irit < m_vprit.size(); irit++)
	{
		GdlSubstitutionItem * pritSub = dynamic_cast<GdlSubstitutionItem *>(m_vprit[irit]);
		if (pritSub)
		{
			Symbol psym = m_vprit[irit]->m_psymInput;
			if (psym && psym->FitsSymbolType(ksymtSpecialUnderscore))
				critIns++;
		}
	}
	return m_critOriginal - critIns;
}
