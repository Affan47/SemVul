sockaddr2text(struct sockaddr *sa, char **address, int zflag)
{
	char	buf[NI_MAXHOST], *token, *bstart, *ep;
	int	addrlen, i, j;
	long	val;

	if (getnameinfo(sa, sysdep_sa_len(sa), buf, sizeof buf, 0, 0,
			allow_name_lookups ? 0 : NI_NUMERICHOST))
		return -1;

	if (zflag == 0) {
		*address = strdup(buf);
		if (!*address)
			return -1;
	} else
		switch (sa->sa_family) {
		case AF_INET:
			addrlen = sizeof "000.000.000.000";
			*address = malloc(addrlen);
			if (!*address)
				return -1;
			buf[addrlen] = '\0';
			bstart = buf;
			**address = '\0';
			while ((token = strsep(&bstart, ".")) != NULL) {
				if (strlen(*address) > 12) {
					free(*address);
					return -1;
				}
				val = strtol(token, &ep, 10);
				if (ep == token || val < (long)0 ||
				    val > (long)UCHAR_MAX) {
					free(*address);
					return -1;
				}
				snprintf(*address + strlen(*address),
				    addrlen - strlen(*address), "%03ld", val);
				if (bstart)
					strlcat(*address, ".", addrlen);
			}
			break;

		case AF_INET6:


			addrlen =
			    sizeof "0000:0000:0000:0000:0000:0000:0000:0000";
			*address = malloc(addrlen);
			if (!*address)
				return -1;

			for (i = 0, j = 0; i < 8; i++) {
				snprintf((*address) + j, addrlen - j,
				    "%02x%02x",
				    ((struct sockaddr_in6 *)sa)->sin6_addr.s6_addr[2*i],
				    ((struct sockaddr_in6 *)sa)->sin6_addr.s6_addr[2*i + 1]);
				j += 4;
				(*address)[j] =
				    (j < (addrlen - 1)) ? ':' : '\0';
				j++;
			}
			break;

		default:
			*address = strdup("<error>");
			if (!*address)
				return -1;
		}

	return 0;
}
