gretl_print_stop_tempfile_read (PRN *prn, FILE *fp)
{
    if (prn == NULL || prn->fp == NULL ||
	prn->fname == NULL || fp == NULL) {
	return E_DATA;
    }

    prn->savepos = ftell(fp);
    fclose(fp);

    return 0;
}
