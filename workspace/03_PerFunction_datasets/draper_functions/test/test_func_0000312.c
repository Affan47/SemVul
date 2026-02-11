TMP_to_BUF(const GEN_PAR * pg, OUT_PAR * po)
{
	int n_rows, n_cols;

	if (pg->td == NULL)
		return ERROR;
	if (n_commands < 0)
		return 0;
	rewind(pg->td);

	cleanup_o(po);


	size_PicBuf(pg, po, &n_rows, &n_cols);

	if ((po->picbuf = allocate_PicBuf(pg, n_rows, n_cols)) == NULL) {
		Eprintf
		    ("Fatal error: cannot allocate %d*%d picture buffer\n",
		     n_rows, n_cols);
		return ERROR;
	}


	tmpfile_to_PicBuf(pg, po);

	return 0;
}
