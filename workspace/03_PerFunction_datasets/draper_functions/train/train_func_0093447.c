getHeaderLabel(UT_uint32 indx) const
{
	UT_return_val_if_fail(m_pSS, NULL);
	switch(indx)
	{
		case 0: return m_pSS->getValue(XAP_STRING_ID_DLG_History_Path);
		case 1: return m_pSS->getValue(XAP_STRING_ID_DLG_History_Version);
		case 2: return m_pSS->getValue(XAP_STRING_ID_DLG_History_Created);
		case 3: return m_pSS->getValue(XAP_STRING_ID_DLG_History_LastSaved);
		case 4: return m_pSS->getValue(XAP_STRING_ID_DLG_History_EditTime);
		case 5: return m_pSS->getValue(XAP_STRING_ID_DLG_History_Id);

		default:;
	}

	UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
	return NULL;
}
