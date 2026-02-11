reverse(void) const
{
	PX_ChangeRecord_RemoveStyle * pcr
		= new PX_ChangeRecord_RemoveStyle(getRevType(),m_position,m_indexAP,getXID());
	UT_ASSERT_HARMLESS(pcr);
	return pcr;
}
