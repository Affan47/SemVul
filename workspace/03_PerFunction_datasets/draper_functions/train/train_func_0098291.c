user_var_get_value_and_type (const char *name,
				   GretlType *type)
{
    user_var *u = get_user_var_by_name(name);
    void *ret = NULL;

    if (u != NULL) {
	ret = u->ptr;
	*type = u->type;
    } else {
	*type = GRETL_TYPE_NONE;
    }

    return ret;
}
