iter_region_sep_op (GelCtx *ctx, GelETree *n)
{
	GelETree *from, *to, *by = NULL;
	GelETree *vect = NULL;
	GelMatrix *mat;
	int bysgn = 1, cmp, initcmp, count, i;
	mpw_t tmp;
	if (n->op.oper == GEL_E_REGION_SEP_BY) {
		GEL_GET_LRR (n, from, by, to);
		if G_UNLIKELY (from->type != GEL_VALUE_NODE ||
			       to->type != GEL_VALUE_NODE ||
			       by->type != GEL_VALUE_NODE) {
			gel_errorout (_("Vector building only works on numbers"));
			return;
		}
		initcmp = cmp = mpw_cmp (from->val.value, to->val.value);
		bysgn = mpw_sgn (by->val.value);

		if G_UNLIKELY ((cmp > 0 && bysgn > 0) ||
			       (cmp != 0 && bysgn == 0) ||
			       (cmp < 0 && bysgn < 0)) {

			gel_errorout (_("Impossible arguments to vector building operator"));
			return;
		}
	} else {
		GEL_GET_LR (n, from, to);
		if G_UNLIKELY (from->type != GEL_VALUE_NODE ||
			       to->type != GEL_VALUE_NODE) {
			gel_errorout (_("Vector building only works on numbers"));
			return;
		}
		initcmp = cmp = mpw_cmp (from->val.value, to->val.value);
		if (cmp > 0)
			bysgn = -1;
	}

	count = 0;
	mpw_init_set (tmp, from->val.value);
	for (;;) {
		GelETree *t = gel_makenum (tmp);

		t->any.next = vect;
		vect = t;
		count ++;

		if (cmp == 0 || cmp != initcmp)
			break;

		if (by != NULL)
			mpw_add (tmp, tmp, by->val.value);
		else if (bysgn == 1)
			mpw_add_ui (tmp, tmp, 1);
		else
			mpw_sub_ui (tmp, tmp, 1);

		cmp = mpw_cmp (tmp, to->val.value);

		if (cmp != 0 && cmp != initcmp)
			break;
	}
	mpw_clear (tmp);

	mat = gel_matrix_new ();
	gel_matrix_set_size (mat, count, 1, FALSE );

	for (i = count-1; i >= 0; i--) {
		GelETree *t = vect;
		gel_matrix_index (mat, i, 0) = t;
		vect = vect->any.next;
		t->any.next = NULL;
	}

	freetree_full (n, TRUE , FALSE );
	n->type = GEL_MATRIX_NODE;
	n->mat.matrix = gel_matrixw_new_with_matrix (mat);
	n->mat.quoted = TRUE;
}
