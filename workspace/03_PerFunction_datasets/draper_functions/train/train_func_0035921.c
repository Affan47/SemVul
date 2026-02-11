mag_g_rm_vint(mag_t *g, int min_len, int min_nsr, int min_ovlp)
{
	int i;
	for (i = 0; i < g->v.n; ++i) {
		magv_t *p = &g->v.a[i];
		if (p->len >= 0 && p->len < min_len && p->nsr < min_nsr)
			mag_v_transdel(g, p, min_ovlp);
	}
}
