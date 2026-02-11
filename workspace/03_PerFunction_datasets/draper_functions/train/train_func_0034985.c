destroy_user_vars_via_callback (int type)
{
    user_var **delvars = NULL;
    int i, j, n = 0;
    int err = 0;

    for (i=0; i<n_vars; i++) {
	if (uvars[i]->level == 0 && uvars[i]->type == type) {
	    n++;
	}
    }

    if (n == 0) {
	return 0;
    }

    delvars = malloc(n * sizeof *delvars);
    if (delvars == NULL) {
	return E_ALLOC;
    }

    j = 0;
    for (i=0; i<n_vars; i++) {
	if (uvars[i]->level == 0 && uvars[i]->type == type) {
	    delvars[j++] = uvars[i];
	}
    }

    for (j=0; j<n && !err; j++) {
	err = (*user_var_callback)(delvars[j]->name,
				   delvars[j]->type,
				   UVAR_DELETE);
    }

    free(delvars);

    return err;
}
