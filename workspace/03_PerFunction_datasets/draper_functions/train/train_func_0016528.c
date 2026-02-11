addLanguagePatternMap (const langType language, const char* ptrn)
{
	vString* const str = vStringNewInit (ptrn);
	parserDefinition* lang;
	Assert (0 <= language  &&  language < (int) LanguageCount);
	lang = LanguageTable [language];
	if (lang->currentPatterns == NULL)
		lang->currentPatterns = stringListNew ();
	stringListAdd (lang->currentPatterns, str);
}
