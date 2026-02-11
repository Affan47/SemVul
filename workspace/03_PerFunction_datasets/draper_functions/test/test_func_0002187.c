matrix_bundle_calc (NODE *l, NODE *r, int op, parser *p)
{
    NODE *ret = aux_matrix_node(p);
    gretl_matrix *ml, *mr;
    gretl_matrix *mtmp = NULL;

    if (ret == NULL) {
	return NULL;
    }

    if (l->t == BUNDLE) {
	mtmp = ml = gretl_bundle_get_payload_matrix(l->v.b, &p->err);
	mr = r->v.m;
    } else {
	ml = l->v.m;
	mtmp = mr = gretl_bundle_get_payload_matrix(r->v.b, &p->err);
    }

    if (!p->err) {
	ret->v.m = real_matrix_calc(ml, mr, op, &p->err);
    }

    gretl_matrix_free(mtmp);

    return ret;
}
