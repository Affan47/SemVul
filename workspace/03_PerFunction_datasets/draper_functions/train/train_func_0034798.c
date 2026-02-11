get_all_option_strings (int *pn)
{
    char **optstrs;
    int i, n = 0;

    for (i=0; gretl_opts[i].ci != 0; i++) {
	n++;
    }

    optstrs = strings_array_new(n);

    if (optstrs != NULL) {
	for (i=0; i<n; i++) {
	    optstrs[i] = gretl_strdup(gretl_opts[i].longopt);
	    if (optstrs[i] == NULL) {
		strings_array_free(optstrs, n);
		optstrs = NULL;
		break;
	    }
	}
    }

    if (optstrs != NULL) {
	strings_array_sort(&optstrs, &n, OPT_U);
	*pn = n;
    }

    return optstrs;
}
