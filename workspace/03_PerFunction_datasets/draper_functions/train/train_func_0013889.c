execute_and_consume(DBPROCESS *dbproc, const char *fmt, ...)
{
	va_list ap;
	char *buffer;

	va_start(ap, fmt);
	if (ast_vasprintf(&buffer, fmt, ap) < 0) {
		va_end(ap);
		return 1;
	}
	va_end(ap);

	if (dbfcmd(dbproc, buffer) == FAIL) {
		free(buffer);
		return 1;
	}

	free(buffer);

	if (dbsqlexec(dbproc) == FAIL) {
		return 1;
	}


	while (dbresults(dbproc) != NO_MORE_RESULTS) {
		while (dbnextrow(dbproc) != NO_MORE_ROWS);
	}

	return 0;
}
