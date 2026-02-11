getListValue(UT_uint32 item, UT_uint32 column) const
{
	UT_return_val_if_fail(m_pDoc, NULL);

	UT_String S;
	time_t tT;
	struct tm * tM;
	char * s;

	switch(column)
	{
		case 0:
			UT_String_sprintf(S,"%d",m_pDoc->getHistoryNthId(item));
			return g_strdup(S.c_str());

		case 1:
			{
				tT = m_pDoc->getHistoryNthTimeStarted(item);
				tM = localtime(&tT);
				s = (char*)g_try_malloc(30);
				if(!s)
					return NULL;

				size_t len = strftime(s,30,"%c",tM);
				if(!len)
				{
					FREEP(s);
					return NULL;
				}

				return s;
			}

		case 2:
			{
				UT_return_val_if_fail(m_pSS, NULL);

				const char * pszS;
				if(m_pDoc->getHistoryNthAutoRevisioned(item))
					pszS = m_pSS->getValue(XAP_STRING_ID_DLG_MB_Yes);
				else
					pszS = m_pSS->getValue(XAP_STRING_ID_DLG_MB_No);

				UT_return_val_if_fail(pszS, NULL);

				return g_strdup(pszS);
			}

		default:;
	}

	UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
	return NULL;
}
