ct_callback(CS_CONTEXT * ctx, CS_CONNECTION * con, CS_INT action, CS_INT type, CS_VOID * func)
{
	int (*funcptr) (void *, void *, void *) = (int (*)(void *, void *, void *)) func;

	tdsdump_log(TDS_DBG_FUNC, "ct_callback(%p, %p, %d, %d, %p)\n", ctx, con, action, type, func);

	tdsdump_log(TDS_DBG_FUNC, "ct_callback() action = %s\n", CS_GET ? "CS_GET" : "CS_SET");

	if (!ctx && !con)
		return CS_FAIL;

	if (action == CS_GET) {
		switch (type) {
		case CS_CLIENTMSG_CB:
			*(void **) func = (CS_VOID *) (con ? con->_clientmsg_cb : ctx->_clientmsg_cb);
			return CS_SUCCEED;
		case CS_SERVERMSG_CB:
			*(void **) func = (CS_VOID *) (con ? con->_servermsg_cb : ctx->_servermsg_cb);
			return CS_SUCCEED;
		default:
			fprintf(stderr, "Unknown callback %d\n", type);
			*(void **) func = NULL;
			return CS_SUCCEED;
		}
	}

	switch (type) {
	case CS_CLIENTMSG_CB:
		if (con)
			con->_clientmsg_cb = (CS_CLIENTMSG_FUNC) funcptr;
		else
			ctx->_clientmsg_cb = (CS_CLIENTMSG_FUNC) funcptr;
		break;
	case CS_SERVERMSG_CB:
		if (con)
			con->_servermsg_cb = (CS_SERVERMSG_FUNC) funcptr;
		else
			ctx->_servermsg_cb = (CS_SERVERMSG_FUNC) funcptr;
		break;
	}
	return CS_SUCCEED;
}
