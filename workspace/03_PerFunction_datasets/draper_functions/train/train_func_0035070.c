freeParserResources (void)
{
	unsigned int i;
	for (i = 0  ;  i < LanguageCount  ;  ++i)
	{
		parserDefinition* const lang = LanguageTable [i];
		freeList (&lang->currentPatterns);
		freeList (&lang->currentExtensions);
		eFree (lang->name);
		lang->name = NULL;
		eFree (lang);
	}
	if (LanguageTable != NULL)
		eFree (LanguageTable);
	LanguageTable = NULL;
	LanguageCount = 0;
}
