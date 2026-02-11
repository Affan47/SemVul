gretl_scalar_add (const char *name, double val)
{
    user_var *u;
    int level = gretl_function_depth();
    int err = 0;

    u = get_user_var_by_name(name);

    if (u != NULL) {
	if (u->type == GRETL_TYPE_DOUBLE) {
	    *(double *) u->ptr = val;
	} else {
	    err = E_TYPES;
	}
	return err;
    } else {
	double *px = malloc(sizeof *px);

	if (px == NULL) {
	    err = E_ALLOC;
	} else {
	    *px = val;
	    err = real_user_var_add(name, GRETL_TYPE_DOUBLE,
				    px, OPT_NONE);
	}

	if (!err && level == 0 && scalar_edit_callback != NULL) {
	    scalar_edit_callback();
	}
    }

    return err;
}
