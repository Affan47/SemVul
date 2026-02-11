builtin_parkcall(struct ast_channel *chan, struct ast_channel *peer, struct ast_bridge_config *config, const char *code, int sense, void *data)
{
	struct ast_channel *parker;
	struct ast_channel *parkee;
	struct ast_park_call_args args = { 0, };


	if (ast_channel_state(chan) != AST_STATE_UP) {


		if (ast_answer(chan)) {
			return -1;
		}


		if (ast_safe_sleep(chan, 1000)) {
			return -1;
		}
	}


	set_peers(&parker, &parkee, peer, chan, sense);
	return masq_park_call(parkee, parker, &args) ? AST_FEATURE_RETURN_SUCCESS : -1;
}
