s_insert_filter(s_filter_cb_t callback)
{
	s_filter_t *nf = calloc(1, sizeof(s_filter_t));
	if(!nf)
		return NULL;

	nf->callback = callback;
	nf->next = filters;
	filters = nf;
	return nf;
}
