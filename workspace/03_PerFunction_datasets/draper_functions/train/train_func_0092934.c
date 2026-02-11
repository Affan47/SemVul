nlmsvc_mark_host(void *data, struct nlm_host *hint)
{
	struct nlm_host *host = data;

	if ((hint->net == NULL) ||
	    (host->net == hint->net))
		host->h_inuse = 1;
	return 0;
}
