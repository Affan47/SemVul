lwres_gethostbyname_r(const char *name, struct hostent *resbuf,
		char *buf, int buflen, int *error)
{
	struct hostent *he;
	int res;

	he = lwres_getipnodebyname(name, AF_INET, 0, error);
	if (he == NULL)
		return (NULL);
	res = copytobuf(he, resbuf, buf, buflen);
	lwres_freehostent(he);
	if (res != 0) {
		errno = ERANGE;
		return (NULL);
	}
	return (resbuf);
}
