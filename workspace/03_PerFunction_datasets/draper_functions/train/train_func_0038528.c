popfile(void)
{
	struct parsefile *pf = g_parsefile;

	INT_OFF;
	if (pf->pf_fd >= 0)
		close(pf->pf_fd);
	free(pf->buf);
	while (pf->strpush)
		popstring();
	g_parsefile = pf->prev;
	free(pf);
	INT_ON;
}
