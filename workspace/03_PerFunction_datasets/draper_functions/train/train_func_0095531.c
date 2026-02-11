getResultValue(UT_uint32 indx) const
{
	UT_return_val_if_fail(m_pSS, NULL);

	UT_String S1, S2;
	struct tm * tM;
	char * s;

	switch(indx)
	{
		case 0:
			if(m_iVersionOfDiff == 0xffffffff)
			{

				return g_strdup(m_pSS->getValue(XAP_STRING_ID_DLG_DocComparison_Identical));
			}
			else if(m_iVersionOfDiff == 0)
			{

				return g_strdup(m_pSS->getValue(XAP_STRING_ID_DLG_DocComparison_Unrelated));
			}
			else
			{

				S1 = m_pSS->getValue(XAP_STRING_ID_DLG_DocComparison_Siblings);
				S1 += "; ";
				S1 += m_pSS->getValue(XAP_STRING_ID_DLG_DocComparison_Diverging);

				tM = localtime(&m_tTimeOfDiff);
				s = (char*)g_try_malloc(30);
				strftime(s,30,"%c",tM);

				UT_String_sprintf(S2, S1.c_str(), m_iVersionOfDiff, s);
				FREEP(s);

				return g_strdup(S2.c_str());
			}

		case 1:
			if(m_iVersionOfDiff == 0xffffffff)
			{

				return g_strdup(m_pSS->getValue(XAP_STRING_ID_DLG_DocComparison_TestSkipped));
			}
			else if(m_iPosOfDiff == 0xffffffff)
			{

				return g_strdup(m_pSS->getValue(XAP_STRING_ID_DLG_DocComparison_Identical));
			}
			else
			{
				const char *s2 = m_pSS->getValue(XAP_STRING_ID_DLG_DocComparison_DivergingPos);
				UT_String_sprintf(S2, s2, m_iPosOfDiff);

				return g_strdup(S2.c_str());
			}

		case 2:
			if(m_iVersionOfDiff == 0xffffffff || m_iPosOfDiff != 0xffffffff)
			{


				return g_strdup(m_pSS->getValue(XAP_STRING_ID_DLG_DocComparison_TestSkipped));
			}
			else if(m_iPosOfFmtDiff == 0xffffffff)
			{

				return g_strdup(m_pSS->getValue(XAP_STRING_ID_DLG_DocComparison_Identical));
			}
			else
			{
				const char * s2 = m_pSS->getValue(XAP_STRING_ID_DLG_DocComparison_DivergingPos);
				UT_String_sprintf(S2, s2, m_iPosOfFmtDiff);

				return g_strdup(S2.c_str());
			}

		case 3:
			if(m_iVersionOfDiff == 0xffffffff)
			{

				return g_strdup(m_pSS->getValue(XAP_STRING_ID_DLG_DocComparison_TestSkipped));
			}
			else if(m_bStylesEqual)
			{

				return g_strdup(m_pSS->getValue(XAP_STRING_ID_DLG_DocComparison_Identical));
			}
			else
			{
				return g_strdup(m_pSS->getValue(XAP_STRING_ID_DLG_DocComparison_Different));
			}

		default:;
	}

	UT_ASSERT_HARMLESS(UT_SHOULD_NOT_HAPPEN);
	return NULL;
}
