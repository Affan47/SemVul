list_bool_comp (NODE *l, NODE *r, int f, int reversed,
			     parser *p)
{
    NODE *ret = aux_vec_node(p, p->dset->n);

    if (ret != NULL && starting(p)) {
	int *list = node_get_list(l, p);
	double *x = ret->v.xvec;
	double xit, targ = NADBL;
	double *tvec = NULL;
	int i, t;

	if (r->t == NUM) {
	    targ = r->v.xval;
	} else {
	    tvec = r->v.xvec;
	}

	if (reversed) {
	    f = reversed_comp(f);
	}

	if (list != NULL) {
	    for (t=p->dset->t1; t<=p->dset->t2; t++) {
		if (tvec != NULL) {
		    targ = tvec[t];
		}
		if (na(targ)) {
		    x[t] = NADBL;
		    continue;
		}
		x[t] = 1.0;
		for (i=1; i<=list[0]; i++) {
		    xit = p->dset->Z[list[i]][t];
		    if (na(xit)) {
			x[t] = NADBL;
			break;
		    } else if (f == B_EQ && xit != targ) {
			x[t] = 0.0;
		    } else if (f == B_NEQ && xit == targ) {
			x[t] = 0.0;
		    } else if (f == B_LT && xit >= targ) {
			x[t] = 0.0;
		    } else if (f == B_GT && xit <= targ) {
			x[t] = 0.0;
		    } else if (f == B_LTE && xit > targ) {
			x[t] = 0.0;
		    } else if (f == B_GTE && xit < targ) {
			x[t] = 0.0;
		    }
		}
	    }
	    free(list);
	}
    }

    return ret;
}
