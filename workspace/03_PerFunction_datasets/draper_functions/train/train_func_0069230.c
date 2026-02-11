matrix_isnan_node (NODE *n, parser *p)
{
    NODE *ret = aux_matrix_node(p);

    if (ret != NULL && starting(p)) {
	const gretl_matrix *m = n->v.m;

	if (m->rows == 0 || m->cols == 0) {
	    p->err = E_DATA;
	} else {
	    ret->v.m = gretl_matrix_alloc(m->rows, m->cols);
	    if (ret->v.m == NULL) {
		p->err = E_ALLOC;
	    } else {
		int i, n = m->rows * m->cols;

		for (i=0; i<n; i++) {
		    ret->v.m->val[i] = isnan(m->val[i]);
		}
	    }
	}
    }

    return ret;
}
