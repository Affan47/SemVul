GMT_native_write_grd_info (struct GRD_HEADER *header)
{


	GMT_LONG err;
	FILE *fp = NULL;

	if (!strcmp (header->name, "=")) {
#ifdef SET_IO_MODE
		GMT_setmode (GMT_OUT);
#endif
		fp = GMT_stdout;
	}
	else if ((fp = GMT_fopen (header->name, "rb+")) == NULL && (fp = GMT_fopen (header->name, "wb")) == NULL)
		return (GMT_GRDIO_CREATE_FAILED);

	GMT_err_trap (GMT_native_write_grd_header (fp, header));

	if (fp != GMT_stdout) GMT_fclose (fp);

	return (GMT_NOERROR);
}
