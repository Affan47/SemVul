bam_maqcns_call(int n, const bam_pileup1_t *pl, bam_maqcns_t *bm)
{
	glf1_t *g;
	uint32_t x;
	if (n) {
		g = bam_maqcns_glfgen(n, pl, 0xf, bm);
		x = g->depth == 0? (0xfU<<28 | 0xfU<<24) : glf2cns(g, (int)(bm->q_r + 0.5));
		free(g);
	} else x = 0xfU<<28 | 0xfU<<24;
	return x;
}
