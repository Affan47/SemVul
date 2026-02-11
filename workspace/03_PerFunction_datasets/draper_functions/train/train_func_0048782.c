interpret_simple (FcFormatContext *c,
		  FcPattern       *pat,
		  FcStrBuf        *buf)
{
    FcPatternElt *e;
    FcBool        add_colon = FcFalse;
    FcBool        add_elt_name = FcFalse;
    int           idx;
    FcChar8      *else_string;

    if (consume_char (c, ':'))
	add_colon = FcTrue;

    if (!read_word (c))
	return FcFalse;

    idx = -1;
    if (consume_char (c, '['))
    {
	idx = strtol ((const char *) c->format, (char **) &c->format, 10);
	if (idx < 0)
	{
	    message ("expected non-negative number at %d",
		     c->format-1 - c->format_orig + 1);
	    return FcFalse;
	}
	if (!expect_char (c, ']'))
	    return FcFalse;
    }

    if (consume_char (c, '='))
	add_elt_name = FcTrue;


    else_string = NULL;
    if (consume_char (c, ':'))
    {
	FcChar8 *orig;

	orig = c->word;
	c->word = c->word + strlen ((const char *) c->word) + 1;

	if (!expect_char (c, '-') ||
	    !read_chars (c, '|'))
	{
	    c->word = orig;
	    return FcFalse;
	}
	else_string = c->word;
	c->word = orig;
    }

    e = FcPatternObjectFindElt (pat,
				FcObjectFromName ((const char *) c->word));
    if (e || else_string)
    {
	FcValueListPtr l = NULL;

	if (add_colon)
	    FcStrBufChar (buf, ':');
	if (add_elt_name)
	{
	    FcStrBufString (buf, c->word);
	    FcStrBufChar (buf, '=');
	}

	if (e)
	    l = FcPatternEltValues(e);

	if (idx != -1)
	{
	    while (l && idx > 0)
	    {
		l = FcValueListNext(l);
		idx--;
	    }
	    if (l && idx == 0)
	    {
		if (!FcNameUnparseValue (buf, &l->value, '\0'))
		    return FcFalse;
	    }
	    else goto notfound;
        }
	else if (l)
	{
	    FcNameUnparseValueList (buf, l, '\0');
	}
	else
	{
    notfound:
	    if (else_string)
		FcStrBufString (buf, else_string);
	}
    }

    return FcTrue;
}
