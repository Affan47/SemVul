dbstrbuild(DBPROCESS * dbproc, char *charbuf, int bufsize, char *text, char *formats, ...)
{
	va_list ap;
	int rc;
	int resultlen;

	tdsdump_log(TDS_DBG_FUNC, "dbstrbuild(%p, %s, %d, %s, %s, ...)\n", dbproc, charbuf, bufsize, text, formats);
	CHECK_NULP(charbuf, "dbstrbuild", 2, FAIL);
	CHECK_NULP(text, "dbstrbuild", 4, FAIL);
	CHECK_NULP(formats, "dbstrbuild", 5, FAIL);

	va_start(ap, formats);
	rc = tds_vstrbuild(charbuf, bufsize, &resultlen, text, TDS_NULLTERM, formats, TDS_NULLTERM, ap);
	charbuf[resultlen] = '\0';
	va_end(ap);
	return rc == TDS_SUCCEED ? SUCCEED : FAIL;
}
