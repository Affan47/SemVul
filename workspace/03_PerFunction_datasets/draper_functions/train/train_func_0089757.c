sig_dcc_destroyed(SERVER_DCC_REC *dcc)
{
	if (!IS_DCC_SERVER(dcc))
		return;

	if (dcc->sendbuf != NULL)
		net_sendbuffer_destroy(dcc->sendbuf, FALSE);
}
