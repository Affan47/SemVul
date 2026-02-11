getCaret(const std::string& sID) const
{
	UT_sint32 i= 0;
	for(i=0; i<m_vecCarets.getItemCount();i++)
	{
		if(m_vecCarets.getNthItem(i)->getID() == sID)
		{
			return m_vecCarets.getNthItem(i);
		}
	}
	return NULL;
}
