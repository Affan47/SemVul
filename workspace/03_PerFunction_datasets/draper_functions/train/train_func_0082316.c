dbsetopt(DBPROCESS * dbproc, int option, const char *char_param, int int_param)
{
	char *cmd;
	RETCODE rc;

	tdsdump_log(TDS_DBG_FUNC, "dbsetopt(%p, %d, %s, %d)\n", dbproc, option, char_param, int_param);
	CHECK_DBPROC();
	DBPERROR_RETURN(IS_TDSDEAD(dbproc->tds_socket), SYBEDDNE);
	CHECK_NULP(char_param, "dbsetopt", 3, FAIL);

	if ((option < 0) || (option >= DBNUMOPTIONS)) {
		dbperror(dbproc, SYBEUNOP, 0);
		return FAIL;
	}
	dbproc->dbopts[option].factive = 1;
	switch (option) {
	case DBARITHABORT:
	case DBARITHIGNORE:
	case DBCHAINXACTS:
	case DBFIPSFLAG:
	case DBISOLATION:
	case DBNOCOUNT:
	case DBNOEXEC:
	case DBPARSEONLY:
	case DBSHOWPLAN:
	case DBSTORPROCID:
	case DBQUOTEDIDENT:

		if (asprintf(&cmd, "set %s on\n", dbproc->dbopts[option].text) < 0) {
			return FAIL;
		}
		rc = dbstring_concat(&(dbproc->dboptcmd), cmd);
		free(cmd);
		return rc;
		break;
	case DBNATLANG:
	case DBDATEFIRST:
	case DBDATEFORMAT:

		if (asprintf(&cmd, "set %s %s\n", dbproc->dbopts[option].text, char_param) < 0) {
			return FAIL;
		}
		rc = dbstring_concat(&(dbproc->dboptcmd), cmd);
		free(cmd);
		return rc;
		break;
	case DBOFFSET:


		break;
	case DBROWCOUNT:


		break;
	case DBSTAT:


		break;
	case DBTEXTLIMIT:


		break;
	case DBTEXTSIZE:


		break;
	case DBAUTH:

		break;
	case DBNOAUTOFREE:

		break;
	case DBBUFFER:


		{
			int nrows;


			if( !char_param )
				char_param = "100";

			nrows = atoi(char_param);

			nrows = (nrows < 0 )? 100 : nrows;

			if( 1 < nrows && nrows <= 2147483647 ) {
				buffer_set_capacity(dbproc, nrows);
				return SUCCEED;
			}
		}
		break;
	case DBPRCOLSEP:
	case DBPRLINELEN:
	case DBPRLINESEP:
		rc = dbstring_assign(&(dbproc->dbopts[option].param), char_param);
		return rc;
	case DBPRPAD:


		if (int_param) {
			rc = dbstring_assign(&(dbproc->dbopts[option].param), char_param? char_param : " ");
		} else {
			rc = dbstring_assign(&(dbproc->dbopts[option].param), NULL);
		}
		return rc;
		break;
	default:
		break;
	}
	tdsdump_log(TDS_DBG_FUNC, "UNIMPLEMENTED dbsetopt(option = %d)\n", option);
	return FAIL;
}
