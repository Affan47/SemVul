gel_matrixw_set_region_etree (GelMatrixW *m, GelETree *src,
			      int *destx, int *desty,
			      int w, int h)
{
	int i, j;
	int xmax, ymax;

	g_return_if_fail (m != NULL);
	g_return_if_fail (src != NULL);
	g_return_if_fail (destx != NULL);
	g_return_if_fail (desty != NULL);
	g_return_if_fail (w >= 0);
	g_return_if_fail (h >= 0);

#ifdef MATRIX_DEBUG
	printf ("%s\n", G_GNUC_PRETTY_FUNCTION);
#endif

	if (m->tr) {
		int t;
		int *tmp = destx;
		destx = desty;
		desty = tmp;
		t = w;
		w = h;
		h = t;
	}

	xmax = getmax (destx, w);
	ymax = getmax (desty, h);

	internal_make_private (m, MAX (xmax+1, m->regw), MAX (ymax+1, m->regh),
			       TRUE );
	ensure_at_least_size (m, xmax+1, ymax+1);

	g_assert (m->regx == NULL && m->regy == NULL);

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			GelETree *t = gel_matrix_index (m->m, destx[i], desty[j]);
			gel_matrix_index (m->m, destx[i], desty[j]) = gel_copynode (src);
			if (t != NULL)
				gel_freetree (t);
		}
	}
}
