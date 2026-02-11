_purgeRevisionTable()
{
	UT_VECTOR_PURGEALL(AD_Revision*, m_vRevisions);
	m_vRevisions.clear();
}
