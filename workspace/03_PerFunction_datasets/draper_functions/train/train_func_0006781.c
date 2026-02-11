mkenvelope(struct name *np)
{
	size_t	epsize;
	char	*ep;
	char	*realname = NULL, *sourceaddr = NULL,
		*localpart = NULL, *domainpart = NULL,
		*cp, *rp, *xp, *ip;
	struct str	in, out;
	int	level = 0, hadphrase = 0;

	in.s = np->n_fullname;
	in.l = strlen(in.s);
	mime_fromhdr(&in, &out, TD_ICONV);
	rp = ip = ac_alloc(strlen(out.s) + 1);
	for (cp = out.s; *cp; cp++) {
		switch (*cp) {
		case '"':
			while (*cp) {
				if (*++cp == '"')
					break;
				if (*cp == '\\' && cp[1])
					cp++;
				*rp++ = *cp;
			}
			break;
		case '<':
			while (cp > out.s && blankchar(cp[-1]&0377))
				cp--;
			rp = ip;
			xp = out.s;
			if (xp < &cp[-1] && *xp == '"' && cp[-1] == '"') {
				xp++;
				cp--;
			}
			while (xp < cp)
				*rp++ = *xp++;
			hadphrase = 1;
			goto done;
		case '(':
			if (level++)
				goto dfl;
			if (hadphrase++ == 0)
				rp = ip;
			break;
		case ')':
			if (--level)
				goto dfl;
			break;
		case '\\':
			if (level && cp[1])
				cp++;
			goto dfl;
		default:
		dfl:
			*rp++ = *cp;
		}
	}
done:	*rp = '\0';
	if (hadphrase)
		realname = ip;
	free(out.s);
	localpart = savestr(np->n_name);
	if ((cp = strrchr(localpart, '@')) != NULL) {
		*cp = '\0';
		domainpart = &cp[1];
	}
	ep = salloc(epsize = strlen(np->n_fullname) * 2 + 40);
	snprintf(ep, epsize, "(%s %s %s %s)",
			realname ? imap_quotestr(realname) : "NIL",
			sourceaddr ? imap_quotestr(sourceaddr) : "NIL",
			localpart ? imap_quotestr(localpart) : "NIL",
			domainpart ? imap_quotestr(domainpart) : "NIL");
	ac_free(ip);
	return ep;
}
