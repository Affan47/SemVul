dcc_server_input(SERVER_DCC_REC *dcc)
{
	char *str;
	int ret;

	g_return_if_fail(IS_DCC_SERVER(dcc));

	do {
		ret = net_sendbuffer_receive_line(dcc->sendbuf, &str, 1);

		if (ret == -1) {

			dcc_close(DCC(dcc));
			break;
		}

		if (ret > 0) {
			dcc->transfd += ret;
			signal_emit("dcc server message", 2, dcc, str);
		}

		if (dcc->connection_established) {


			dcc->handle = NULL;
			dcc_close(DCC(dcc));
			break;
		}
	} while (ret > 0);
}
