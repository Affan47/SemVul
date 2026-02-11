ast_bridge_end_dtmf(struct ast_channel *chan, char digit, struct timeval start, const char *why)
{
	int dead;
	long duration;

	ast_channel_lock(chan);
	dead = ast_test_flag(ast_channel_flags(chan), AST_FLAG_ZOMBIE)
		|| (ast_channel_softhangup_internal_flag(chan)
			& ~(AST_SOFTHANGUP_ASYNCGOTO | AST_SOFTHANGUP_UNBRIDGE));
	ast_channel_unlock(chan);
	if (dead) {

		return;
	}

	duration = ast_tvdiff_ms(ast_tvnow(), start);
	ast_senddigit_end(chan, digit, duration);
	ast_log(LOG_DTMF, "DTMF end '%c' simulated on %s due to %s, duration %ld ms\n",
		digit, ast_channel_name(chan), why, duration);
}
