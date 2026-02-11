vector_sort (NODE *l, int f, parser *p)
{
    NODE *ret = (l->t == VEC)? aux_vec_node(p, p->dset->n) :
	aux_matrix_node(p);

    if (ret != NULL && starting(p)) {
	if (l->t == VEC) {
	    p->err = sort_series(l->v.xvec, ret->v.xvec, f, p->dset);
	} else if (gretl_is_null_matrix(l->v.m)) {
	    p->err = E_DATA;
	} else {
	    int n = gretl_vector_get_length(l->v.m);

	    if (n > 0) {
		ret->v.m = gretl_matrix_copy(l->v.m);
		if (ret->v.m == NULL) {
		    p->err = E_ALLOC;
		} else {
		    double *x = ret->v.m->val;

		    qsort(x, n, sizeof *x, (f == F_SORT)? gretl_compare_doubles :
			  gretl_inverse_compare_doubles);
		}
	    } else {
		p->err = E_TYPES;
	    }
	}

	if (p->err) {
	    free(ret);
	    ret = NULL;
	}
    }

    return ret;
}
