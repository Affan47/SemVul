start_spying(struct ast_autochan *autochan, const char *spychan_name, struct ast_audiohook *audiohook)
{
	int res = 0;
	struct ast_channel *peer = NULL;

	ast_log(LOG_NOTICE, "Attaching %s to %s\n", spychan_name, ast_channel_name(autochan->chan));

	ast_set_flag(audiohook, AST_AUDIOHOOK_TRIGGER_SYNC | AST_AUDIOHOOK_SMALL_QUEUE);
	res = ast_audiohook_attach(autochan->chan, audiohook);

	if (!res && ast_test_flag(ast_channel_flags(autochan->chan), AST_FLAG_NBRIDGE) && (peer = ast_bridged_channel(autochan->chan))) {
		ast_softhangup(peer, AST_SOFTHANGUP_UNBRIDGE);
	}
	return res;
}
