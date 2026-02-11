ast_can_pickup(struct ast_channel *chan)
{
	if (!ast_channel_pbx(chan) && !ast_channel_masq(chan) && !ast_test_flag(ast_channel_flags(chan), AST_FLAG_ZOMBIE)
		&& (ast_channel_state(chan) == AST_STATE_RINGING
			|| ast_channel_state(chan) == AST_STATE_RING


			|| ast_channel_state(chan) == AST_STATE_DOWN)
		&& !ast_channel_datastore_find(chan, &pickup_active, NULL)) {
		return 1;
	}
	return 0;
}
