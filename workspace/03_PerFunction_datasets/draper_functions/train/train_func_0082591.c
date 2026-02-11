user_var_destroy (user_var *u)
{
    int free_val = 1;

    if (var_is_shell(u)) {
	free_val = 0;
    } else if (u->type == GRETL_TYPE_MATRIX) {


	if (data_is_bundled(u->ptr, "user_var_destroy")) {
	    free_val = 0;
	}
    }

    if (free_val) {
	uvar_free_value(u);
    }

    free(u);
}
