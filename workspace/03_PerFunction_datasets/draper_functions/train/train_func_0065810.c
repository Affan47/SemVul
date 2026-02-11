bcp_getl(LOGINREC * login)
{
	TDSLOGIN *tdsl = login->tds_login;

	tdsdump_log(TDS_DBG_FUNC, "bcp_getl(%p)\n", login);

	return (tdsl->bulk_copy);
}
