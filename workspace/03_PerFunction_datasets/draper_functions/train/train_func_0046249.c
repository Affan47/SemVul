ast_pbx_hangup_handler_run(struct ast_channel *chan)
{
	struct ast_hangup_handler_list *handlers;
	struct ast_hangup_handler *h_handler;

	ast_channel_lock(chan);
	handlers = ast_channel_hangup_handlers(chan);
	if (AST_LIST_EMPTY(handlers)) {
		ast_channel_unlock(chan);
		return 0;
	}

	if (ast_channel_cdr(chan) && ast_opt_end_cdr_before_h_exten) {
		ast_cdr_end(ast_channel_cdr(chan));
	}


	ast_softhangup_nolock(chan, AST_SOFTHANGUP_APPUNLOAD);

	for (;;) {
		handlers = ast_channel_hangup_handlers(chan);
		h_handler = AST_LIST_REMOVE_HEAD(handlers, node);
		if (!h_handler) {
			break;
		}


		manager_event(EVENT_FLAG_DIALPLAN, "HangupHandlerRun",
			"Channel: %s\r\n"
			"Uniqueid: %s\r\n"
			"Handler: %s\r\n",
			ast_channel_name(chan),
			ast_channel_uniqueid(chan),
			h_handler->args);
		ast_channel_unlock(chan);

		ast_app_exec_sub(NULL, chan, h_handler->args, 1);
		ast_free(h_handler);

		ast_channel_lock(chan);
	}
	ast_channel_unlock(chan);
	return 1;
}
