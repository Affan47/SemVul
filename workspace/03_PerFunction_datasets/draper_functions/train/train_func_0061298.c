dbsetifile(char *filename)
{
	tdsdump_log(TDS_DBG_FUNC, "dbsetifile(%s)\n", filename? filename : "0x00");
	if (filename == NULL) {
		dbperror(NULL, SYBENULP, 0);
		return;
	}
	tds_set_interfaces_file_loc(filename);
}
