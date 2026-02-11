mt_lazy_flush(BGZF *fp)
{
	mtaux_t *mt = fp->mt;
	if (fp->block_offset) mt_queue(fp);
	if (mt->curr == mt->n_blks)
		return mt_flush(fp);
	return -1;
}
