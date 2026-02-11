cha_set_language(char *langstr)
{
    Cha_lang = CHASEN_LANG_JA;

    if (langstr[0] == 'j') {
	Cha_lang = CHASEN_LANG_JA;
    } else if (langstr[0] == 'e') {
	Cha_lang = CHASEN_LANG_EN;
    }
}
