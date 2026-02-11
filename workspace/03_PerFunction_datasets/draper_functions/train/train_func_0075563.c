find_cid(struct rfc2045 *p, const char *cidurl)
{
const char *cid=rfc2045_content_id(p);

	if (cid && strcmp(cid, cidurl) == 0)
		return (p);

	for (p=p->firstpart; p; p=p->next)
	{
	struct rfc2045 *q;

		if (p->isdummy)	continue;

		q=find_cid(p, cidurl);
		if (q)	return (q);
	}
	return (0);
}
