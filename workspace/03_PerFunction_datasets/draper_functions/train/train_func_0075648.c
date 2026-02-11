fetch_eof(struct worker *wrk, struct http_conn *htc)
{
	int i;

	assert(wrk->busyobj->body_status == BS_EOF);
	i = wrk->busyobj->vfp->bytes(wrk, htc, SSIZE_MAX);
	if (i < 0)
		return (-1);
	return (0);
}
