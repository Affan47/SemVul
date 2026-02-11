parse_strings(u_char *p, u_char *q, int max,
			 char *s, u_char *ofs, u_char *found)
{
	int i, j, ns;

	if (p == q)
		return -EINVAL;
	ns = 0; j = 0;
	for (i = 0; i < max; i++) {
		if (*p == 0xff)
			break;
		ofs[i] = j;
		ns++;
		for (;;) {
			s[j++] = (*p == 0xff) ? '\0' : *p;
			if ((*p == '\0') || (*p == 0xff))
				break;
			if (++p == q)
				return -EINVAL;
		}
		if ((*p == 0xff) || (++p == q))
			break;
	}
	if (found) {
		*found = ns;
		return 0;
	}

	return (ns == max) ? 0 : -EINVAL;
}
