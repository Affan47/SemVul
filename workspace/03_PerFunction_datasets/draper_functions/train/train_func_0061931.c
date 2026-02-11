CheckLBsInRules(Symbol psymTable)
{
	m_fLB = false;
	m_fCrossLB = false;
	m_critPreLB = 0;
	m_critPostLB = 0;
	m_fReproc = false;

	int critPreLB = 0;
	int critPostLB = 0;

	for (size_t iprule = 0; iprule < m_vprule.size(); iprule++)
	{
		if (m_vprule[iprule]->IsBadRule())
			continue;

		bool fAnyLB = m_vprule[iprule]->CheckLBsInRules(psymTable, &critPreLB, &critPostLB);
		m_fLB = (m_fLB || fAnyLB);
		if (critPreLB > 0 && critPostLB > 0)
		{
			m_fCrossLB = true;
			m_critPreLB = max(m_critPreLB, critPreLB);
			m_critPostLB = max(m_critPostLB, critPostLB);
		}

		if (m_vprule[iprule]->HasReprocessing())
			m_fReproc = true;
	}
	Assert(!m_fCrossLB || m_fLB);
	Assert(!m_fCrossLB || m_critPreLB > 0 || m_critPostLB > 0);
}
