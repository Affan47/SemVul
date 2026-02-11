ast_aoc_manager_event(const struct ast_aoc_decoded *decoded, struct ast_channel *chan)
{
	struct ast_str *msg;

	if (!decoded || !(msg = ast_str_create(1024))) {
		return -1;
	}

	switch (decoded->msg_type) {
	case AST_AOC_S:
		if (chan) {
			aoc_s_event(decoded, chan, &msg);
			ast_manager_event(chan, EVENT_FLAG_AOC, "AOC-S", "%s", ast_str_buffer(msg));
		}
		break;
	case AST_AOC_D:
		if (chan) {
			aoc_d_event(decoded, chan, &msg);
			ast_manager_event(chan, EVENT_FLAG_AOC, "AOC-D", "%s", ast_str_buffer(msg));
		}
		break;
	case AST_AOC_E:
		{
			struct ast_channel *chans[1];
			aoc_e_event(decoded, chan, &msg);
			chans[0] = chan;
			ast_manager_event_multichan(EVENT_FLAG_AOC, "AOC-E", chan ? 1 : 0, chans, "%s", ast_str_buffer(msg));
		}
		break;
	default:

		break;
	}

	ast_free(msg);
	return 0;
}
