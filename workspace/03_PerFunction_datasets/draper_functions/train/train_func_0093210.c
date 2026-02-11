read_word (FcFormatContext *c)
{
    FcChar8 *p;

    p = c->word;

    while (*c->format)
    {
	if (*c->format == '\\')
	{
	    c->format++;
	    if (*c->format)
	      *p++ = escaped_char (*c->format++);
	    continue;
	}
	else if (FcCharIsPunct (*c->format))
	    break;

	*p++ = *c->format++;
    }
    *p = '\0';

    if (p == c->word)
    {
	message ("expected identifier at %d",
		 c->format - c->format_orig + 1);
	return FcFalse;
    }

    return FcTrue;
}
