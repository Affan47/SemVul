pr_expand(proto, maxwidth)
	char *proto;
	int maxwidth;
{
	register char *p;
	register int c;
	int where;

	mp = message;

	if (*proto == '\0')
		return ("");

	for (p = proto;  *p != '\0';  p++)
	{
		switch (*p)
		{
		default:
			ap_char(*p);
			break;
		case '\\':
			p++;
			ap_char(*p);
			break;
		case '?':
			if ((c = *++p) == '\0')
				--p;
			else
			{
				where = 0;
				p = wherechar(p, &where);
				if (!cond(c, where))
					p = skipcond(p);
			}
			break;
		case ':':
			p = skipcond(p);
			break;
		case '.':
			break;
		case '%':
			if ((c = *++p) == '\0')
				--p;
			else
			{
				where = 0;
				p = wherechar(p, &where);
				protochar(c, where,
#if EDITOR
					(proto == editproto));
#else
					0);
#endif

			}
			break;
		}
	}

	if (mp == message)
		return (NULL);
	if (maxwidth > 0 && mp >= message + maxwidth)
	{


		return (mp - maxwidth);
	}
	return (message);
}
