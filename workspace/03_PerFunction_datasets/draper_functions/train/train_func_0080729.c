awk_split(const char *s, node *spl, char **slist)
{
	int l, n;
	char c[4];
	char *s1;
	regmatch_t pmatch[2];


	*slist = s1 = xzalloc(strlen(s) * 2 + 3);
	strcpy(s1, s);

	c[0] = c[1] = (char)spl->info;
	c[2] = c[3] = '\0';
	if (*getvar_s(intvar[RS]) == '\0')
		c[2] = '\n';

	n = 0;
	if ((spl->info & OPCLSMASK) == OC_REGEXP) {
		if (!*s)
			return n;
		n++;
		do {
			l = strcspn(s, c+2);
			if (regexec(icase ? spl->r.ire : spl->l.re, s, 1, pmatch, 0) == 0
			 && pmatch[0].rm_so <= l
			) {
				l = pmatch[0].rm_so;
				if (pmatch[0].rm_eo == 0) {
					l++;
					pmatch[0].rm_eo++;
				}
				n++;
			} else {
				pmatch[0].rm_eo = l;
				if (s[l])
					pmatch[0].rm_eo++;
			}
			memcpy(s1, s, l);

			do {
				s1[l] = '\0';
			} while (++l < pmatch[0].rm_eo);
			nextword(&s1);
			s += pmatch[0].rm_eo;
		} while (*s);
		return n;
	}
	if (c[0] == '\0') {
		while (*s) {
			*s1++ = *s++;
			*s1++ = '\0';
			n++;
		}
		return n;
	}
	if (c[0] != ' ') {
		if (icase) {
			c[0] = toupper(c[0]);
			c[1] = tolower(c[1]);
		}
		if (*s1)
			n++;
		while ((s1 = strpbrk(s1, c)) != NULL) {
			*s1++ = '\0';
			n++;
		}
		return n;
	}

	while (*s) {
		s = skip_whitespace(s);
		if (!*s)
			break;
		n++;
		while (*s && !isspace(*s))
			*s1++ = *s++;
		*s1++ = '\0';
	}
	return n;
}
