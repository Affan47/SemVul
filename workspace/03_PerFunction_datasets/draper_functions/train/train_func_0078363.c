skip_expr (FcFormatContext *c)
{
    while(*c->format && *c->format != '}')
    {
	switch (*c->format)
	{
	case '\\':
	    c->format++;
	    if (*c->format)
		c->format++;
	    continue;
	case '%':
	    if (!skip_percent (c))
		return FcFalse;
	    continue;
	}
	c->format++;
    }

    return FcTrue;
}
