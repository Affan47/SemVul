_clear()
{
	for(UT_sint32 i = 0; i < m_vRev.getItemCount(); i++)
	{
		delete (PP_Revision *) m_vRev.getNthItem(i);
	}

	m_vRev.clear();
	m_bDirty = true;
	m_pLastRevision = NULL;
}
