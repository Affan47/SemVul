removeCaret(const std::string& sID)
{
	for(UT_sint32 i = 0; i < m_vecCarets.getItemCount(); i++)
	{
		GR_Caret* pC = m_vecCarets.getNthItem(i);
		if (pC->getID() == sID)
		{
			DELETEP(pC);
			m_vecCarets.deleteNthItem(i);
		}
	}
}
