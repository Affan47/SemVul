chasen_fparse_tostr(FILE * fp_in)
{
    char line[CHA_INPUT_SIZE];

    if (cha_fgets(line, sizeof(line), fp_in) == NULL)
	return NULL;

    if (chasen_sparse_main(line, NULL))
	return NULL;

    return cha_get_output();
}
