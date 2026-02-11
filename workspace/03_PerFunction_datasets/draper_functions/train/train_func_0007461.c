rfc822_print_common_nameaddr(const struct rfc822addr *addrs,
					char *(*decode_func)(const char *,
							     const char *, int),
					const char *chset,
					void (*print_func)(char, void *),
					void *ptr)
{
	size_t n=1;
	char *addrbuf, *namebuf;
	char *p, *q;
	int print_braces=0;

	if (addrs->tokens)
		rfc822tok_print(addrs->tokens,
				rfc822_print_common_nameaddr_cntlen, &n);


	p=addrbuf=malloc(n);

	if (!addrbuf)
		return -1;

	if (addrs->tokens)
		rfc822tok_print(addrs->tokens,
				rfc822_print_common_nameaddr_saveaddr, &p);

	*p=0;

	n=1;

	rfc822_prname_int(addrs,
			  rfc822_print_common_nameaddr_cntlen, &n);

	p=namebuf=malloc(n);

	if (!p)
	{
		free(addrbuf);
		return -1;
	}

	rfc822_prname_int(addrs,
			  rfc822_print_common_nameaddr_saveaddr, &p);

	*p=0;

	p=(*decode_func)(namebuf, chset, 0);

	free(namebuf);
	if (!p)
	{
		free(addrbuf);
		return -1;
	}

	for (namebuf=p; *p; p++)
	{
		print_braces=1;
		(*print_func)(*p, ptr);
	}
	free(namebuf);

	p=(*decode_func)(addrbuf, chset, 1);
	free(addrbuf);

	if (!p)
		return -1;

	if (print_braces)
		(*print_func)(' ', ptr);

	for (q=p; *q; ++q)
		if (*q != '.' && *q != '@' && strchr(RFC822_SPECIALS, *q))
		{
			print_braces=1;
			break;
		}

	if (print_braces)
		(*print_func)('<', ptr);

	for (addrbuf=p; *p; p++)
		(*print_func)(*p, ptr);

	if (print_braces)
		(*print_func)('>', ptr);

	free(addrbuf);
	return (0);
}
