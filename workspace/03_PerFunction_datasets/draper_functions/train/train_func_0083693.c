parseEnumFields (vString * const ident, objcToken what)
{
	static parseNext prev = NULL;

	if (prev != NULL)
	{
		comeAfter = prev;
		prev = NULL;
	}

	switch (what)
	{
	case ObjcIDENTIFIER:
		addTag (ident, K_ENUM);
		prev = comeAfter;
		waitedToken = Tok_COMA;

		fallBackToken = Tok_CurlR;
		fallback = comeAfter;
		comeAfter = parseEnumFields;
		toDoNext = &tillTokenOrFallBack;
		break;

	case Tok_CurlR:
		toDoNext = comeAfter;
		popEnclosingContext ();
		break;

	default:

		break;
	}
}
