SetMinus_op (GelCtx *ctx, GelETree * * a, gboolean *exception)
{
	GelMatrixW *m1, *m2;
	int w, h, i, j;
	int len;
	GSList *list, *li;
	GelETree *n;
	GelMatrix *nm;

	if G_UNLIKELY ( ! check_argument_matrix_or_null (a, 0, "SetMinus") ||
			! check_argument_matrix_or_null (a, 1, "SetMinus"))
		return NULL;

	if (a[0]->type == GEL_NULL_NODE) {
		return gel_makenum_null ();
	} else if (a[1]->type == GEL_NULL_NODE) {
		return gel_copynode (a[0]);
	}

	m1 = a[0]->mat.matrix;
	m2 = a[1]->mat.matrix;

	list = NULL;
	len = 0;

	w = gel_matrixw_width (m1);
	h = gel_matrixw_height (m1);

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			GelETree *t = gel_matrixw_index (m1, i, j);
			if ( ! symbolic_isinmatrix (t, m2)) {
				if (t == the_zero)
					list = g_slist_prepend (list, NULL);
				else
					list = g_slist_prepend (list, gel_copynode (t));
				len ++;
			}
		}
	}
	if (list == NULL) {
		return gel_makenum_null ();
	}

	nm = gel_matrix_new ();
	gel_matrix_set_size (nm, len, 1, FALSE );

	li = list;
	for (i = len-1; i >= 0; i--) {
		gel_matrix_index (nm, i, 0) = li->data;
		li = li->next;
	}
	g_slist_free (list);

	GEL_GET_NEW_NODE (n);
	n->type = GEL_MATRIX_NODE;
	n->mat.matrix = gel_matrixw_new_with_matrix (nm);
	n->mat.quoted = a[0]->mat.quoted;

	return n;
}
