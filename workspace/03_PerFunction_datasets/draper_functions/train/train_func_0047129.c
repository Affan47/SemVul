grab_transfer(struct ast_channel *chan, char *exten, size_t exten_len, const char *context)
{
	int res;


	res = ast_stream_and_wait(chan, "pbx-transfer", AST_DIGIT_ANY);
	ast_stopstream(chan);


	if (res) {
		exten[0] = (char)res;
	}


	res = ast_app_dtget(chan, context, exten, exten_len, 100, 1000);

	return res;
}
