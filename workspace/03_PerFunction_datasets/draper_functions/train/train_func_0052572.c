removeAllHigherOrEqualIds(UT_uint32 iId)
{
	for(UT_sint32 i = 0; i < m_vRev.getItemCount(); i++)
	{
		PP_Revision * r = (PP_Revision *)m_vRev.getNthItem(i);

		if(iId <= r->getId())
		{
			delete r;
			m_vRev.deleteNthItem(i);
			--i;
		}
	}

	m_bDirty = true;
	m_pLastRevision = NULL;
}
