SetLexerLanguage(const char *languageName) {
	lexLanguage = SCLEX_CONTAINER;
	lexCurrent = LexerModule::Find(languageName);
	if (!lexCurrent)
		lexCurrent = LexerModule::Find(SCLEX_NULL);
	if (lexCurrent)
		lexLanguage = lexCurrent->GetLanguage();
	int bits = lexCurrent ? lexCurrent->GetStyleBitsNeeded() : 5;
	vs.EnsureStyle((1 << bits) - 1);
}
