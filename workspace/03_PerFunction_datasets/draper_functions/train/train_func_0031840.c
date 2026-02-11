get_kalman_matrix_id (const char **ps)
{
    const char *test;
    int i, n;

    for (i=0; i<K_MMAX; i++) {
	test = K_input_mats[i].name;
	n = strlen(test);
	if (!strncmp(*ps, test, n) && (*ps)[n] == ' ') {
	    *ps += n + 1;
	    return K_input_mats[i].sym;
	}
    }


    gretl_errmsg_sprintf("kalman: invalid input '%s'", *ps);

    return -1;
}
