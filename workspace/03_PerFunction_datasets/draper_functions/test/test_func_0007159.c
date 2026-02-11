scalar_isnan_node (NODE *n, parser *p)
{
    NODE *ret = aux_scalar_node(p);

    if (ret != NULL) {
	double x = node_get_scalar(n, p);

	if (!p->err) {
	    ret->v.xval = isnan(x);
	}
    }

    return ret;
}
