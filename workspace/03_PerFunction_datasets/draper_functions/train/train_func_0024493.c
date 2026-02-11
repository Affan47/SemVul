lhs_copy_node (parser *p)
{
    NODE *n = new_node(p->targ);

    if (n != NULL) {
	if (p->targ == NUM) {
	    n->v.xval = gretl_scalar_get_value(p->lh.name, NULL);
	} else if (p->targ == VEC) {
	    n->v.xvec = p->dset->Z[p->lh.v];
	} else if (p->targ == STR) {
	    n->v.str = gretl_strdup(get_string_by_name(p->lh.name));
	} else {
	    n->v.m = p->lh.m0;
	}
    }

    return n;
}
