speech_load(struct ast_channel *chan, const char *vdata)
{
	int res = 0;
	struct ast_speech *speech = find_speech(chan);
	char *data;
	AST_DECLARE_APP_ARGS(args,
		AST_APP_ARG(grammar);
		AST_APP_ARG(path);
	);

	data = ast_strdupa(vdata);
	AST_STANDARD_APP_ARGS(args, data);

	if (speech == NULL)
		return -1;

	if (args.argc != 2)
		return -1;


	res = ast_speech_grammar_load(speech, args.grammar, args.path);

	return res;
}
