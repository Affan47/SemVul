ast_recvtext(struct ast_channel *chan, int timeout)
{
	int res;
	char *buf = NULL;
	struct timeval start = ast_tvnow();
	int ms;

	while ((ms = ast_remaining_ms(start, timeout))) {
		struct ast_frame *f;

		if (ast_check_hangup(chan)) {
			break;
		}
		res = ast_waitfor(chan, ms);
		if (res <= 0)  {
			break;
		}
		f = ast_read(chan);
		if (f == NULL) {
			break;
		}
		if (f->frametype == AST_FRAME_CONTROL && f->subclass.integer == AST_CONTROL_HANGUP) {
			ast_frfree(f);
			break;
		} else if (f->frametype == AST_FRAME_TEXT) {
			buf = ast_strndup((char *) f->data.ptr, f->datalen);
			ast_frfree(f);
			break;
		}
		ast_frfree(f);
	}
	return buf;
}
