user_var_count_for_type (GretlType type)
{
    int i, n = 0;

    for (i=0; i<n_vars; i++) {
	if (uvars[i]->type == type) {
	    n++;
	}
    }

    return n;
}
