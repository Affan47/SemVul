single_string_func (NODE *n, int f, parser *p)
{
    NODE *ret = aux_string_node(p);

    if (ret != NULL && starting(p)) {
	const char *s = n->v.str;

	if (f == F_ARGNAME) {
	    ret->v.str = gretl_func_get_arg_name(s, &p->err);
	} else if (f == F_BACKTICK) {
	    ret->v.str = gretl_backtick(s, &p->err);
	} else if (f == F_STRSTRIP) {
	    ret->v.str = gretl_strstrip_copy(s, &p->err);
	} else if (f == F_FIXNAME) {
	    ret->v.str = calloc(VNAMELEN, 1);
	    normalize_join_colname(ret->v.str, s, 0);
	} else {
	    p->err = E_DATA;
	}
    }

    return ret;
}
