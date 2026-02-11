gretl_print_close_stream (PRN *prn)
{
    if (prn != NULL && prn->fp != NULL) {
	fclose(prn->fp);
	prn->fp = NULL;
	free(prn->fname);
	prn->fname = NULL;
    }
}
