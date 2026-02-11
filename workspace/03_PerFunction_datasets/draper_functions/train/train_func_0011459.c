servlist_sanitize_hostname (char *host)
{
	char *ret, *c, *e;

	ret = strdup (host);

	c = strchr  (ret, ':');
	e = strrchr (ret, ':');


	if (c && c == e)
		*c = '/';

	return ret;
}
