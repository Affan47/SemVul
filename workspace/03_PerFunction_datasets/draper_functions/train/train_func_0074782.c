escape_keyword_value (const char *value, int *free_value)
{
    char *ret, *t;
    const char *s;

    for (s = value; *s != '\0'; s++)
    {
	char c;

	c = *s;
	if (c == '\t'
	    || c == '\n'
	    || c == '\\'
	    || c == ' '
	    || c == '$')
	{
	    break;
	}
    }

    if (*s == '\0')
    {
	*free_value = 0;
	return (char *) value;
    }

    ret = xmalloc (strlen (value) * 4 + 1);
    *free_value = 1;

    for (s = value, t = ret; *s != '\0'; s++, t++)
    {
	switch (*s)
	{
	default:
	    *t = *s;
	    break;
	case '\t':
	    *t++ = '\\';
	    *t = 't';
	    break;
	case '\n':
	    *t++ = '\\';
	    *t = 'n';
	    break;
	case '\\':
	    *t++ = '\\';
	    *t = '\\';
	    break;
	case ' ':
	    *t++ = '\\';
	    *t++ = '0';
	    *t++ = '4';
	    *t = '0';
	    break;
	case '$':
	    *t++ = '\\';
	    *t++ = '0';
	    *t++ = '4';
	    *t = '4';
	    break;
	}
    }

    *t = '\0';

    return ret;
}
