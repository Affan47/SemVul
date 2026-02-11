steal_matrix_by_name (const char *name)
{
    gretl_matrix *ret = NULL;

    if (name != NULL && *name != '\0') {
	user_var *u;

	u = get_user_var_of_type_by_name(name, GRETL_TYPE_MATRIX);

	if (u != NULL) {
	    ret = user_var_steal_value(u);
	}
    }

    return ret;
}
