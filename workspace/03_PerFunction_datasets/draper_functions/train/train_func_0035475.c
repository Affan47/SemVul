MRns_name_ntol(const u_char *src, u_char *dst, size_t dstsiz) {
	const u_char *cp;
	u_char *dn, *eom;
	u_char c;
	u_int n;

	cp = src;
	dn = dst;
	eom = dst + dstsiz;

	if (dn >= eom) {
		errno = EMSGSIZE;
		return (-1);
	}
	while ((n = *cp++) != 0) {
		if ((n & NS_CMPRSFLGS) != 0) {

			errno = EMSGSIZE;
			return (-1);
		}
		*dn++ = n;
		if (dn + n >= eom) {
			errno = EMSGSIZE;
			return (-1);
		}
		for ((void)NULL; n > 0; n--) {
			c = *cp++;
			if (isupper(c))
				*dn++ = tolower(c);
			else
				*dn++ = c;
		}
	}
	*dn++ = '\0';
	return (dn - dst);
}
