escape_chars (FcFormatContext *c,
	      const FcChar8   *str,
	      FcStrBuf        *buf)
{


    if (!expect_char (c, '(') ||
	!read_chars (c, ')') ||
	!expect_char (c, ')'))
	return FcFalse;

    while(*str)
    {
	FcChar8 *p;

	p = (FcChar8 *) strpbrk ((const char *) str, (const char *) c->word);
	if (p)
	{
	    FcStrBufData (buf, str, p - str);
	    FcStrBufChar (buf, c->word[0]);
	    FcStrBufChar (buf, *p);
	    str = p + 1;
	}
	else
	{
	    FcStrBufString (buf, str);
	    break;
	}

    }

    return FcTrue;
}
