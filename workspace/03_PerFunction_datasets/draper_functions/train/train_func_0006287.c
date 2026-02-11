_findFont(const char* pszFontFamily,
										 const char* pszFontStyle,
										 const char* pszFontVariant,
										 const char* pszFontWeight,
										 const char* pszFontStretch,
										 const char* pszFontSize,
										 const char* pszLang)
{
	double dPointSize = UT_convertToPoints(pszFontSize);
	std::string s;


	const char * pStyle = pszFontStyle;
	const char * pVariant = pszFontVariant;
	const char * pWeight = pszFontWeight;
	const char * pStretch = pszFontStretch;

	if(pszFontStyle && *pszFontStyle == 'n')
		pStyle = "";
	else if(pszFontStyle == NULL)
	        pStyle = "";

	if(pszFontVariant && *pszFontVariant == 'n')
		pVariant = "";
	else if(pszFontVariant == NULL)
	        pVariant = "";

	if(pszFontWeight && *pszFontWeight == 'n')
		pWeight = "";
	else if(pszFontWeight == NULL)
	        pWeight = "";

	if(pszFontStretch && *pszFontStretch == 'n')
		pStretch = "";
	else if(pszFontStretch == NULL)
	        pStretch = "";

	if(!pszLang || !*pszLang)
		pszLang = "en-US";

	s = UT_std_string_sprintf("%s, %s %s %s %s",
					  pszFontFamily,
					  pStyle,
					  pVariant,
					  pWeight,
					  pStretch);

	return new GR_PangoFont(s.c_str(), dPointSize, this, pszLang);
}
