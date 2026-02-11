getDocDefaultLangCheckboxLabel(UT_UTF8String &s)
{
	const XAP_StringSet * pSS = XAP_App::getApp()->getStringSet();
	UT_return_if_fail(pSS);

	std::string str;
	pSS->getValueUTF8(XAP_STRING_ID_DLG_ULANG_DefaultLangChkbox, str);
	s = str;
}
