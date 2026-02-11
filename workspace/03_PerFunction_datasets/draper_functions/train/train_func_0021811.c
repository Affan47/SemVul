get_language()
{
	const char * lang = cGetLocalPref("spell_dictionary");
	const char * env_lang[] = {"LC_LANG", "LC_ALL", "LANG", NULL};
	int i=0;

	while(env_lang[i] && (!lang || !lang[0])) {
		lang = getenv(env_lang[i]);
		i++;
	}

	if(!lang || !lang[0])
		lang = "en_GB";

	return lang;
}
