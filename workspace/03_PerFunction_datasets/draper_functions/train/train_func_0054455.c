LOCAL_get_lang(void)
{
	char *lang;

	if (!_lang)
	{
		lang = getenv("LC_ALL");
		if (!lang)
			lang = getenv("LANG");
		if (!lang || !*lang)
			lang = "en_US";
		_lang = STRING_new_zero(lang);
	}

	return _lang;
}
