ast_channel_connected_line_macro(struct ast_channel *autoservice_chan, struct ast_channel *macro_chan, const void *connected_info, int is_caller, int is_frame)
{
	static int deprecation_warning = 0;
	const char *macro;
	const char *macro_args;
	int retval;

	ast_channel_lock(macro_chan);
	macro = pbx_builtin_getvar_helper(macro_chan, is_caller
		? "CONNECTED_LINE_CALLER_SEND_MACRO" : "CONNECTED_LINE_CALLEE_SEND_MACRO");
	macro = ast_strdupa(S_OR(macro, ""));
	macro_args = pbx_builtin_getvar_helper(macro_chan, is_caller
		? "CONNECTED_LINE_CALLER_SEND_MACRO_ARGS" : "CONNECTED_LINE_CALLEE_SEND_MACRO_ARGS");
	macro_args = ast_strdupa(S_OR(macro_args, ""));

	if (ast_strlen_zero(macro)) {
		ast_channel_unlock(macro_chan);
		return -1;
	}

	if (!deprecation_warning) {
		deprecation_warning = 1;
		ast_log(LOG_WARNING, "Usage of CONNECTED_LINE_CALLE[ER]_SEND_MACRO is deprecated.  Please use CONNECTED_LINE_SEND_SUB instead.\n");
	}
	if (is_frame) {
		const struct ast_frame *frame = connected_info;

		ast_connected_line_parse_data(frame->data.ptr, frame->datalen, ast_channel_connected(macro_chan));
	} else {
		const struct ast_party_connected_line *connected = connected_info;

		ast_party_connected_line_copy(ast_channel_connected(macro_chan), connected);
	}
	ast_channel_unlock(macro_chan);

	retval = ast_app_run_macro(autoservice_chan, macro_chan, macro, macro_args);
	if (!retval) {
		struct ast_party_connected_line saved_connected;

		ast_party_connected_line_init(&saved_connected);
		ast_channel_lock(macro_chan);
		ast_party_connected_line_copy(&saved_connected, ast_channel_connected(macro_chan));
		ast_channel_unlock(macro_chan);
		ast_channel_update_connected_line(macro_chan, &saved_connected, NULL);
		ast_party_connected_line_free(&saved_connected);
	}

	return retval;
}
