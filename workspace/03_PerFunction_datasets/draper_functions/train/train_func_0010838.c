guess_language (bool ignore_cc)
{

	char *envvars[3] = { "LANGUAGE", "LC_ALL", "LANG" };
	for (int i = 0; i < 3; ++i) {
		char *lang = getenv (envvars[i]);
		if (!lang)
			continue;
		wxString LL, CC;
		if (ignore_cc)
			split_lang_spec (lang, LL, CC);
		else
			LL = wxString (lang, wxConvUTF8);

		for (int j = 0; j < NUM_LANGUAGES; ++j) {
			if (LL == wxString (languages[j].code, wxConvUTF8)) {

				set_language (languages[j].lang);
				return true;
			}
		}
	}


	if (ignore_cc)
		return false;


	return guess_language (true);
}
