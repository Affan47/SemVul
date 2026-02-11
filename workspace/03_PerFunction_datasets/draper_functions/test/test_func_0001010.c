mm_write_banner(FILE * f, MM_typecode matcode)
{
    char *str = mm_typecode_to_str(matcode);
    int ret_code;

    ret_code = fprintf(f, "%s %s\n", MatrixMarketBanner, str);
    free(str);
    if (ret_code != 2)
	return MM_COULD_NOT_WRITE_FILE;
    else
	return 0;
}
