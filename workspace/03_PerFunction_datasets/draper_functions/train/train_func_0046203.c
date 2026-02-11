user_var_localize (const char *origname,
		       const char *localname,
		       GretlType type)
{
    user_var *u;
    int err = 0;

    if (type == GRETL_TYPE_SCALAR_REF) {
	type = GRETL_TYPE_DOUBLE;
    } else if (type == GRETL_TYPE_MATRIX_REF) {
	type = GRETL_TYPE_MATRIX;
    } else if (type == GRETL_TYPE_BUNDLE_REF) {
	type = GRETL_TYPE_BUNDLE;
    }

    u = get_user_var_of_type_by_name(origname, type);

    if (u == NULL) {
	err = E_DATA;
    } else {
	user_var_set_name(u, localname);
	u->level += 1;
    }

    return err;
}
