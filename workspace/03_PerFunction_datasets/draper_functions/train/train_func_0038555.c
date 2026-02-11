logfile_write(logfile_t *lf, const char *buf)
{
	char datetime[64];
	time_t t;
	struct tm tm;

	return_if_fail(lf != NULL);
	return_if_fail(lf->log_file != NULL);
	return_if_fail(buf != NULL);

	time(&t);
	tm = *localtime(&t);
	strftime(datetime, sizeof(datetime) - 1, "[%d/%m/%Y %H:%M:%S]", &tm);

	fprintf((FILE *) lf->log_file, "%s %s\n", datetime, logfile_strip_control_codes(buf));
	fflush((FILE *) lf->log_file);
}
