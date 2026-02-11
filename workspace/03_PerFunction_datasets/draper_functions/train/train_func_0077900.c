ConstructWindowName(void)
{
	const XAP_StringSet * pSS = XAP_App::getApp()->getStringSet();

	std::string s;
	pSS->getValueUTF8(getWindowTitleStringId(), s);

    s = UT_XML_cloneNoAmpersands( s );
	m_WindowName = BuildWindowName( s.c_str() );
}
