choose_node(graph_t * G, int nG)
{
    int i, k;
    double m, max;
    node_t *choice, *np;
    static int cnt = 0;
#if 0
    double e;
    static double save_e = MAXDOUBLE;
#endif

    cnt++;
    if (GD_move(G) >= MaxIter)
	return NULL;
#if 0
    if ((cnt % 100) == 0) {
	e = total_e(G, nG);
	if (e - save_e > 0)
	    return NULL;
	save_e = e;
    }
#endif
    max = 0.0;
    choice = NULL;
    for (i = 0; i < nG; i++) {
	np = GD_neato_nlist(G)[i];
	if (ND_pinned(np) > P_SET)
	    continue;
	for (m = 0.0, k = 0; k < Ndim; k++)
	    m += (GD_sum_t(G)[i][k] * GD_sum_t(G)[i][k]);

	if (m > max) {
	    choice = np;
	    max = m;
	}
    }
    if (max < Epsilon2)
	choice = NULL;
    else {
	if (Verbose && (cnt % 100 == 0)) {
	    fprintf(stderr, "%.3f ", sqrt(max));
	    if (cnt % 1000 == 0)
		fprintf(stderr, "\n");
	}
#if 0
	e = total_e(G, nG);
	if (fabs((e - save_e) / save_e) < 1e-5) {
	    choice = NULL;
	}
#endif
    }
    return choice;
}
