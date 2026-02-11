uc_split_args(arg, lenp)
    char_u *arg;
    size_t *lenp;
{
    char_u *buf;
    char_u *p;
    char_u *q;
    int len;


    p = arg;
    len = 2;

    while (*p)
    {
	if (p[0] == '\\' && p[1] == '\\')
	{
	    len += 2;
	    p += 2;
	}
	else if (p[0] == '\\' && vim_iswhite(p[1]))
	{
	    len += 1;
	    p += 2;
	}
	else if (*p == '\\' || *p == '"')
	{
	    len += 2;
	    p += 1;
	}
	else if (vim_iswhite(*p))
	{
	    p = skipwhite(p);
	    if (*p == NUL)
		break;
	    len += 3;
	}
	else
	{
	    ++len;
	    ++p;
	}
    }

    buf = alloc(len + 1);
    if (buf == NULL)
    {
	*lenp = 0;
	return buf;
    }

    p = arg;
    q = buf;
    *q++ = '"';
    while (*p)
    {
	if (p[0] == '\\' && p[1] == '\\')
	{
	    *q++ = '\\';
	    *q++ = '\\';
	    p += 2;
	}
	else if (p[0] == '\\' && vim_iswhite(p[1]))
	{
	    *q++ = p[1];
	    p += 2;
	}
	else if (*p == '\\' || *p == '"')
	{
	    *q++ = '\\';
	    *q++ = *p++;
	}
	else if (vim_iswhite(*p))
	{
	    p = skipwhite(p);
	    if (*p == NUL)
		break;
	    *q++ = '"';
	    *q++ = ',';
	    *q++ = '"';
	}
	else
	{
	    *q++ = *p++;
	}
    }
    *q++ = '"';
    *q = 0;

    *lenp = len;
    return buf;
}
