ast_setstate(struct ast_channel *chan, enum ast_channel_state state)
{
	int oldstate = ast_channel_state(chan);
	char name[AST_CHANNEL_NAME], *dashptr;

	if (oldstate == state)
		return 0;

	ast_copy_string(name, ast_channel_name(chan), sizeof(name));
	if ((dashptr = strrchr(name, '-'))) {
		*dashptr = '\0';
	}

	ast_channel_state_set(chan, state);


	ast_devstate_changed_literal(AST_DEVICE_UNKNOWN, (ast_test_flag(ast_channel_flags(chan), AST_FLAG_DISABLE_DEVSTATE_CACHE) ? AST_DEVSTATE_NOT_CACHABLE : AST_DEVSTATE_CACHABLE), name);


	ast_manager_event(chan, EVENT_FLAG_CALL, "Newstate",
		"Channel: %s\r\n"
		"ChannelState: %d\r\n"
		"ChannelStateDesc: %s\r\n"
		"CallerIDNum: %s\r\n"
		"CallerIDName: %s\r\n"
		"ConnectedLineNum: %s\r\n"
		"ConnectedLineName: %s\r\n"
		"Uniqueid: %s\r\n",
		ast_channel_name(chan), ast_channel_state(chan), ast_state2str(ast_channel_state(chan)),
		S_COR(ast_channel_caller(chan)->id.number.valid, ast_channel_caller(chan)->id.number.str, ""),
		S_COR(ast_channel_caller(chan)->id.name.valid, ast_channel_caller(chan)->id.name.str, ""),
		S_COR(ast_channel_connected(chan)->id.number.valid, ast_channel_connected(chan)->id.number.str, ""),
		S_COR(ast_channel_connected(chan)->id.name.valid, ast_channel_connected(chan)->id.name.str, ""),
		ast_channel_uniqueid(chan));

	return 0;
}
