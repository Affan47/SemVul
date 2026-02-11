contextualTillToken (vString * const UNUSED (ident), ocaToken what)
{
	static int parentheses = 0;
	static int bracket = 0;
	static int curly = 0;

	switch (what)
	{
	case Tok_PARL:
		parentheses--;
		break;
	case Tok_PARR:
		parentheses++;
		break;
	case Tok_CurlL:
		curly--;
		break;
	case Tok_CurlR:
		curly++;
		break;
	case Tok_BRL:
		bracket--;
		break;
	case Tok_BRR:
		bracket++;
		break;

	default:
		break;
	}

	if (what == waitedToken && parentheses == 0 && bracket == 0 && curly == 0)
		toDoNext = comeAfter;

	else if (what == OcaKEYWORD_end)
	{
		popStrongContext ();
		toDoNext = &globalScope;
	}
}
