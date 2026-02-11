generate_string (const char *s, DATASET *dset, int *err)
{
    parser p;
    char *ret = NULL;

    *err = realgen(s, &p, dset, NULL, P_STRING | P_PRIVATE);

    if (!*err) {
	if (p.ret->t == STR) {
	    ret = gretl_strdup(p.ret->v.str);
	} else {
	    *err = E_TYPES;
	}
    } else if (*err == 1) {
	*err = E_PARSE;
    }

    gen_cleanup(&p);

    return ret;
}
