fax_gateway_request_t38(struct fax_gateway *gateway, struct ast_channel *chan, struct ast_frame *f)
{
	struct ast_frame *fp;
	struct ast_control_t38_parameters t38_parameters = {
		.request_response = AST_T38_REQUEST_NEGOTIATE,
	};
	struct ast_frame control_frame = {
		.src = "res_fax",
		.frametype = AST_FRAME_CONTROL,
		.datalen = sizeof(t38_parameters),
		.subclass.integer = AST_CONTROL_T38_PARAMETERS,
		.data.ptr = &t38_parameters,
	};

	struct ast_fax_session_details *details = find_details(chan);

	if (!details) {
		ast_log(LOG_ERROR, "no FAX session details found on chan %s for T.38 gateway session, odd\n", ast_channel_name(chan));
		ast_framehook_detach(chan, gateway->framehook);
		return f;
	}

	t38_parameters_fax_to_ast(&t38_parameters, &details->our_t38_parameters);
	ao2_ref(details, -1);

	if (!(fp = ast_frisolate(&control_frame))) {
		ast_log(LOG_ERROR, "error generating T.38 request control frame on chan %s for T.38 gateway session\n", ast_channel_name(chan));
		return f;
	}

	gateway->t38_state = T38_STATE_NEGOTIATING;
	gateway->timeout_start = ast_tvnow();
	details->gateway_timeout = FAX_GATEWAY_TIMEOUT;

	ast_debug(1, "requesting T.38 for gateway session for %s\n", ast_channel_name(chan));
	return fp;
}
