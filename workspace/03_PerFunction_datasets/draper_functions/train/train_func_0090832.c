fm6_api_unitig(int min_match, int64_t l, char *seq)
{
	rld_t *e;
	mag_t *g;
	uint64_t i, *used, *bend, *visited;
	if (min_match < 0) {
		min_match = (int)(fm6_api_seqlen(l, seq, .25) * .33 + .499);
		if (fm_verbose >= 3) fprintf(stderr, "[M::%s] choose k-mer size as %d\n", __func__, min_match);
	}
	for (i = 0; i < l; ++i)
		if (seq[i] > 5) seq[i] = seq_nt6_table[(int)seq[i]];
	e = fm6_build2(l, seq);
	used    = (uint64_t*)xcalloc((e->mcnt[1] + 63)/64, 8);
	bend    = (uint64_t*)xcalloc((e->mcnt[1] + 63)/64, 8);
	visited = (uint64_t*)xcalloc((e->mcnt[1] + 63)/64, 8);
	g = calloc(1, sizeof(mag_t));
	unitig_core(e, min_match, 0, 1, used, bend, visited, 0, &g->v);
	mag_g_build_hash(g);
	free(used); free(bend); free(visited);
	rld_destroy(e);
	return g;
}
