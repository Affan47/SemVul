getport(char *host)
{
	char *p, *q;
	q = strchr(host, ':');
	if (q)
		p = mystrdup(q+1);
	else
		p = mystrdup("80");
	return p;
}
