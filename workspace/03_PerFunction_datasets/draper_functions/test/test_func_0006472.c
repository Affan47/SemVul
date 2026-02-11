viterbi_free(struct viterbi *v)
{
	int i;

	if (v) {
		g_free(v->output);

		for (i = 0; i < v->nstates; i++) {
			g_free(v->metrics[i]);
			g_free(v->history[i]);
		}

		g_free(v);
	}
}
