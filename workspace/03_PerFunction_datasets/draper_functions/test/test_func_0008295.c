FcParseAcceptRejectFont (FcConfigParse *parse, FcElement element)
{
    FcVStack	*vstack;

    while ((vstack = FcVStackPeek (parse)))
    {
	switch ((int) vstack->tag) {
	case FcVStackGlob:
	    if (!FcConfigGlobAdd (parse->config,
				  vstack->u.string,
				  element == FcElementAcceptfont))
	    {
		FcConfigMessage (parse, FcSevereError, "out of memory");
	    }
	    break;
	case FcVStackPattern:
	    if (!FcConfigPatternsAdd (parse->config,
				      vstack->u.pattern,
				      element == FcElementAcceptfont))
	    {
		FcConfigMessage (parse, FcSevereError, "out of memory");
	    }
	    else
		vstack->tag = FcVStackNone;
	    break;
	default:
	    FcConfigMessage (parse, FcSevereWarning, "bad font selector");
	    break;
	}
	FcVStackPopAndDestroy (parse);
    }
}
