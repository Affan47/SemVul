vdi_dns_find_backend(const struct sess *sp, struct vdi_dns *vs)
{
	struct director *ret;
	struct http *hp;
	char *p, *q;
	char hostname[NI_MAXHOST];


	if (sp->wrk->busyobj != NULL && sp->wrk->busyobj->bereq)
		hp = sp->wrk->busyobj->bereq;
	else
		hp = sp->req->http;


	CHECK_OBJ_NOTNULL(hp, HTTP_MAGIC);
	if (http_GetHdr(hp, H_Host, &p) == 0)
		return (NULL);

	q = strchr(p, ':');
	if (q == NULL)
		q = strchr(p, '\0');
	AN(q);

	bprintf(hostname, "%.*s%s", (int)(q - p), p,
	    vs->suffix ? vs->suffix : "");

	ret = vdi_dns_walk_cache(sp, vs, hostname);
	return (ret);
}
