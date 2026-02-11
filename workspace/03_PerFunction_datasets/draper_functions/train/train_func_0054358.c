cmds_abor(CONTEXT *ctx, char *arg)
{
	if (ctx == NULL)
		misc_die(FL, "cmds_abor: ?ctx?");
	arg = arg;


	syslog_write(U_WRN, "'ABOR' from %s", ctx->cli_ctrl->peer);


	client_data_reset(MOD_RESET);


	if (ctx->cli_data == NULL && ctx->srv_data == NULL) {
		client_respond(225, NULL, "ABOR command successful");
		return;
	}


	if (ctx->cli_data != NULL) {
		socket_kill(ctx->cli_data);
		ctx->cli_data = NULL;
		client_respond(426, NULL,
			"Connection closed; transfer aborted");
		client_respond(226, NULL, "ABOR command successful");
	}


	if (ctx->srv_ctrl != NULL) {
#if defined(MSG_OOB)
		char str[4];
		socket_flag(ctx->srv_ctrl, MSG_OOB);
		str[0] = IAC;
		str[1] = IP;
		str[2] = IAC;
		socket_write(ctx->srv_ctrl, str, 3);
		socket_flag(ctx->srv_ctrl, 0);
		str[0] = DM;
		socket_write(ctx->srv_ctrl, str, 1);
#endif
		socket_printf(ctx->srv_ctrl, "ABOR\r\n");
		ctx->expect = EXP_ABOR;
	}
}
