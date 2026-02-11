open_log_file(const char *fname, struct log_file_context *lfc)
{
	lfc->fp = fopen(fname ,"a");
	if (!lfc->fp) {
		syslog(LOG_ERR, "Failed to open log file %s: %s\n" ,
		       fname, strerror(errno));
	} else {
		setvbuf(lfc->fp, NULL,
				use_buffered_io ? _IOFBF : _IONBF,
				BUFSIZ);
		fstat(fileno(lfc->fp), &lfc->stat_buf);
	}
}
