handle_speechdestroy(struct ast_channel *chan, AGI *agi, int argc, const char * const argv[])
{
	if (agi->speech) {
		ast_speech_destroy(agi->speech);
		agi->speech = NULL;
		ast_agi_send(agi->fd, chan, "200 result=1\n");
	} else {
		ast_agi_send(agi->fd, chan, "200 result=0\n");
	}

	return RESULT_SUCCESS;
}
