initializeDParser (const langType language)
{


	const char *const_aliases[] = {"immutable", "nothrow", "pure", "shared", NULL};
	const char **s;

	Lang_d = language;
	buildKeywordHash (language, 6);

	for (s = const_aliases; *s != NULL; s++)
	{
		addKeyword (*s, language, KEYWORD_CONST);
	}

	addKeyword ("alias", language, KEYWORD_TYPEDEF);

	addKeyword ("assert", language, KEYWORD_IF);
	addKeyword ("unittest", language, KEYWORD_BODY);
	addKeyword ("version", language, KEYWORD_NAMESPACE);
}
