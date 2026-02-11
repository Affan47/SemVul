ct_close(CS_CONNECTION * con, CS_INT option)
{
	tdsdump_log(TDS_DBG_FUNC, "ct_close(%p, %d)\n", con, option);

	tds_free_socket(con->tds_socket);
	con->tds_socket = NULL;
	return CS_SUCCEED;
}
