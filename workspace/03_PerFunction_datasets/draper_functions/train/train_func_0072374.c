ses_sm_alloc(void)
{
	struct sessmem *sm;
	unsigned char *p, *q;
	unsigned nws;
	uint16_t nhttp;
	unsigned l, hl;

	if (VSC_C_main->n_sess_mem >= params->max_sess)
		return (NULL);


	nws = params->sess_workspace;
	nhttp = (uint16_t)params->http_max_hdr;
	hl = HTTP_estimate(nhttp);
	l = sizeof *sm + nws + 2 * hl;
	p = malloc(l);
	if (p == NULL)
		return (NULL);
	q = p + l;

	Lck_Lock(&stat_mtx);
	VSC_C_main->n_sess_mem++;
	Lck_Unlock(&stat_mtx);


	memset(p, 0, l - nws);

	sm = (void*)p;
	p += sizeof *sm;
	sm->magic = SESSMEM_MAGIC;
	sm->workspace = nws;
	sm->http[0] = HTTP_create(p, nhttp);
	p += hl;
	sm->http[1] = HTTP_create(p, nhttp);
	p += hl;
	sm->wsp = p;
	p += nws;
	assert(p == q);

	return (sm);
}
