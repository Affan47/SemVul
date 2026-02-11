ConstructWindowName(void)
{
	const XAP_StringSet * pSS = m_pApp->getStringSet();
	gchar * tmp = NULL;
	UT_XML_cloneNoAmpersands(tmp, pSS->getValue(AP_STRING_ID_DLG_WordCount_WordCountTitle));
	BuildWindowName(static_cast<char *>(m_WindowName),static_cast<char*>(tmp),sizeof(m_WindowName));
	FREEP(tmp);
}
