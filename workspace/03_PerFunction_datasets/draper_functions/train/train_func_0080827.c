dblogin(void)
{
	LOGINREC *loginrec;

	tdsdump_log(TDS_DBG_FUNC, "dblogin(void)\n");

	if ((loginrec = malloc(sizeof(LOGINREC))) == NULL) {
		dbperror(NULL, SYBEMEM, errno);
		return NULL;
	}
	if ((loginrec->tds_login = tds_alloc_login()) == NULL) {
		dbperror(NULL, SYBEMEM, errno);
		free(loginrec);
		return NULL;
	}


	tds_set_library(loginrec->tds_login, "DB-Library");

	return loginrec;
}
