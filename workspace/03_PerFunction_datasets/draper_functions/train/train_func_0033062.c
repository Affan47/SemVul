get_named_list_element (NODE *l, NODE *r, parser *p)
{
    NODE *ret = aux_scalar_node(p);

    if (ret != NULL && starting(p)) {
	int *list = node_get_list(l, p);
	int i = node_get_int(r, p);

	if (!p->err) {
	    if (i < 1 || i > list[0]) {
		gretl_errmsg_sprintf("Index value %d is out of bounds", i);
		p->err = E_DATA;
	    } else {
		ret->v.xval = list[i];
	    }
	}
	free(list);
    }

    return ret;
}
