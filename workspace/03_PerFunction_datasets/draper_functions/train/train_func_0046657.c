bcf_write(bcf_t *bp, const bcf_hdr_t *h, const bcf1_t *b)
{
	int i, l = 0;
	if (b == 0) return -1;
	bgzf_write(bp->fp, &b->tid, 4);
	bgzf_write(bp->fp, &b->pos, 4);
	bgzf_write(bp->fp, &b->qual, 4);
	bgzf_write(bp->fp, &b->l_str, 4);
	bgzf_write(bp->fp, b->str, b->l_str);
	l = 12 + b->l_str;
	for (i = 0; i < b->n_gi; ++i) {
		bgzf_write(bp->fp, b->gi[i].data, b->gi[i].len * h->n_smpl);
		l += b->gi[i].len * h->n_smpl;
	}
	return l;
}
