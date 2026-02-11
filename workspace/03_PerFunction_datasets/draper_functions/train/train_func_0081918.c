findLangInfoByLocale(const char* locale)
{
	if (!locale)
		return NULL;

	std::string strISOName(locale, 2);
	std::string strCountryCode;

	if (strlen(locale) == 5)
	{
		strCountryCode = (locale + 3);
	}

	const XAP_LangInfo* cur = langinfo;
	const XAP_LangInfo* temp = NULL;
	for(; cur->fields[0]; ++cur)
	{
		if (strISOName == cur->fields[XAP_LangInfo::isoshortname_idx])
		{
			if (! *cur->fields[XAP_LangInfo::countrycode_idx])
			{
				if (strCountryCode.empty())
					return cur;
				else
					temp = cur;
			}
			else if (strCountryCode == cur->fields[XAP_LangInfo::countrycode_idx])
			{
				return cur;
			}
		}
	}

	if (temp != NULL)
	{
		return temp;
	}

	return NULL;
}
