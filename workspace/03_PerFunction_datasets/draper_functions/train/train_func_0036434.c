set_work_ntime(struct work *work, int ntime)
{
	uint32_t *work_ntime = (uint32_t *)(work->data + 68);

	*work_ntime = htobe32(ntime);
	if (work->ntime) {
		free(work->ntime);
		work->ntime = bin2hex((unsigned char *)work_ntime, 4);
	}
}
