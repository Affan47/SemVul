appendFmt(const gchar ** attributes)
{

	UT_return_val_if_fail (m_pts==PTS_Loading, false);


	UT_return_val_if_fail (NULL != m_fragments.getFirst(), false);


	if (!m_varset.storeAP(attributes,&loading.m_indexCurrentInlineAP))
		return false;

	return true;
}
