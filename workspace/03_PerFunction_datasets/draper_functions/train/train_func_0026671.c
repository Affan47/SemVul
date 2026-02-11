getline_node (NODE *l, NODE *r, parser *p)
{
    NODE *ret = aux_scalar_node(p);

    if (ret != NULL && starting(p)) {
	const char *buf = l->v.str;

	if (l->vname == NULL) {
	    gretl_errmsg_set("getline: the source must be a string variable");
	    p->err = E_TYPES;
	} else if (null_or_empty(r)) {
	    bufgets_finalize(buf);
	} else if (r->vname == NULL) {
	    gretl_errmsg_set("getline: the target must be a string variable");
	} else {
	    p->err = query_bufgets_init(buf);
	    if (!p->err) {
		size_t len = bufgets_peek_line_length(buf);

		if (len == 0) {
		    bufgets_finalize(buf);
		    strcpy(r->v.str, "");
		    ret->v.xval = 0;
		} else {
		    r->v.str = user_string_resize(r->vname, len, &p->err);
		    if (!p->err) {
			bufgets(r->v.str, len, buf);
			strip_newline(r->v.str);
			ret->v.xval = 1;
		    }
		}
	    }
	}
    }

    return ret;
}
