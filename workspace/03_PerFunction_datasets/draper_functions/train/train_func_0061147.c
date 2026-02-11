ast_waitfordigit_full(struct ast_channel *c, int timeout_ms, int audiofd, int cmdfd)
{
	struct timeval start = ast_tvnow();
	int ms;


	if (ast_test_flag(ast_channel_flags(c), AST_FLAG_ZOMBIE) || ast_check_hangup(c))
		return -1;


	ast_set_flag(ast_channel_flags(c), AST_FLAG_END_DTMF_ONLY);


	while ((ms = ast_remaining_ms(start, timeout_ms))) {
		struct ast_channel *rchan;
		int outfd = -1;

		errno = 0;


		rchan = ast_waitfor_nandfds(&c, 1, &cmdfd, (cmdfd > -1) ? 1 : 0, NULL, &outfd, &ms);

		if (!rchan && outfd < 0 && ms) {
			if (errno == 0 || errno == EINTR)
				continue;
			ast_log(LOG_WARNING, "Wait failed (%s)\n", strerror(errno));
			ast_clear_flag(ast_channel_flags(c), AST_FLAG_END_DTMF_ONLY);
			return -1;
		} else if (outfd > -1) {

			ast_log(LOG_WARNING, "The FD we were waiting for has something waiting. Waitfordigit returning numeric 1\n");
			ast_clear_flag(ast_channel_flags(c), AST_FLAG_END_DTMF_ONLY);
			return 1;
		} else if (rchan) {
			int res;
			struct ast_frame *f = ast_read(c);
			if (!f)
				return -1;

			switch (f->frametype) {
			case AST_FRAME_DTMF_BEGIN:
				break;
			case AST_FRAME_DTMF_END:
				res = f->subclass.integer;
				ast_frfree(f);
				ast_clear_flag(ast_channel_flags(c), AST_FLAG_END_DTMF_ONLY);
				return res;
			case AST_FRAME_CONTROL:
				switch (f->subclass.integer) {
				case AST_CONTROL_HANGUP:
					ast_frfree(f);
					ast_clear_flag(ast_channel_flags(c), AST_FLAG_END_DTMF_ONLY);
					return -1;
				case AST_CONTROL_PVT_CAUSE_CODE:
				case AST_CONTROL_RINGING:
				case AST_CONTROL_ANSWER:
				case AST_CONTROL_SRCUPDATE:
				case AST_CONTROL_SRCCHANGE:
				case AST_CONTROL_CONNECTED_LINE:
				case AST_CONTROL_REDIRECTING:
				case AST_CONTROL_UPDATE_RTP_PEER:
				case AST_CONTROL_HOLD:
				case AST_CONTROL_UNHOLD:
				case -1:

					break;
				default:
					ast_log(LOG_WARNING, "Unexpected control subclass '%d'\n", f->subclass.integer);
					break;
				}
				break;
			case AST_FRAME_VOICE:

				if (audiofd > -1) {
					if (write(audiofd, f->data.ptr, f->datalen) < 0) {
						ast_log(LOG_WARNING, "write() failed: %s\n", strerror(errno));
					}
				}
			default:

				break;
			}
			ast_frfree(f);
		}
	}

	ast_clear_flag(ast_channel_flags(c), AST_FLAG_END_DTMF_ONLY);

	return 0;
}
