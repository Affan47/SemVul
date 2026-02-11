db_initialize(int *pargc, char ***pargv)
{
    FILE *f;

    if (*pargc < 2)
	return 0;

    input_db_name = str_dup((*pargv)[0]);
    dump_db_name = str_dup((*pargv)[1]);
    *pargc -= 2;
    *pargv += 2;

    if (!(f = fopen(input_db_name, "r"))) {
	fprintf(stderr, "Cannot open input database file: %s\n",
		input_db_name);
	return 0;
    }
    input_db = f;
    dbpriv_build_prep_table();

    return 1;
}
