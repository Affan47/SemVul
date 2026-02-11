maybe_stack_var (GRETL_VAR *var, CMD *cmd)
{
    int err = 0;

    if (var != NULL) {
	const char *name = gretl_cmd_get_savename(cmd);

	set_as_last_model(var, GRETL_OBJ_VAR);
	if (*name != '\0') {
	    err = real_stack_object(var, GRETL_OBJ_VAR, name, NULL);
	}
    }

    return err;
}
