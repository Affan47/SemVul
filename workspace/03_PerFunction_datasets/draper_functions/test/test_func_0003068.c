pergm_node (NODE *l, NODE *r, parser *p)
{
    NODE *ret = NULL;

    if (!empty_or_num(r)) {

	node_type_error(F_PERGM, 2, NUM, r, p);
    } else if (l->t == MAT && gretl_vector_get_length(l->v.m) == 0) {

	node_type_error(F_PERGM, 1, VEC, l, p);
    } else {
	ret = aux_matrix_node(p);
    }

    if (!p->err) {
	const double *x = NULL;
	int t1 = 0, t2 = 0;
	int width = -1;

	if (l->t == VEC) {
	    x = l->v.xvec;
	    t1 = p->dset->t1;
	    t2 = p->dset->t2;
	} else if (l->t == MAT) {
	    x = l->v.m->val;
	    t1 = 0;
	    t2 = gretl_vector_get_length(l->v.m) - 1;
	}

	if (r != NULL && r->t == NUM) {
	    width = r->v.xval;
	}

	ret->v.m = periodogram_matrix(x, t1, t2, width, &p->err);
    }

    return ret;
}
