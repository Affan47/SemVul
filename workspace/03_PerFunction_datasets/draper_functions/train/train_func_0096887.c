bam_calend(const bam1_core_t *c, const uint32_t *cigar)
{
	int k, end = c->pos;
	for (k = 0; k < c->n_cigar; ++k) {
		int op  = bam_cigar_op(cigar[k]);
		int len = bam_cigar_oplen(cigar[k]);
		if (op == BAM_CBACK) {
			int l, u, v;
			if (k == c->n_cigar - 1) break;
			for (l = k - 1, u = v = 0; l >= 0; --l) {
				int op1  = bam_cigar_op(cigar[l]);
				int len1 = bam_cigar_oplen(cigar[l]);
				if (bam_cigar_type(op1)&1) {
					if (u + len1 >= len) {
						if (bam_cigar_type(op1)&2) v += len - u;
						break;
					} else u += len1;
				}
				if (bam_cigar_type(op1)&2) v += len1;
			}
			end = l < 0? c->pos : end - v;
		} else if (bam_cigar_type(op)&2) end += bam_cigar_oplen(cigar[k]);
	}
	return end;
}
