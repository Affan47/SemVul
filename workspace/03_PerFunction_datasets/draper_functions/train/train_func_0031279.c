bam_readrec(BGZF *fp, void *null, bam1_t *b, int *tid, int *beg, int *end)
{
	int ret;
	if ((ret = bam_read1(fp, b)) >= 0) {
		*tid = b->core.tid; *beg = b->core.pos;
		*end = b->core.pos + (b->core.n_cigar? bam_cigar2rlen(b->core.n_cigar, bam_get_cigar(b)) : 1);
	}
	return ret;
}
