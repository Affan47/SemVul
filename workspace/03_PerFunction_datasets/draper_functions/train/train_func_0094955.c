sayword_exec(struct ast_channel *chan, const char *data)
{
	int res = 0;
	char *s;
	int inum;
	AST_DECLARE_APP_ARGS(args,
		AST_APP_ARG(word1);
		AST_APP_ARG(word2);
		AST_APP_ARG(word5);
		AST_APP_ARG(num);
	);

	if (!data) {
		ast_log(LOG_WARNING, "SayCountPL requires 4 arguments: word-1,word-2,word-5,number\n");
		return -1;
	}

	s = ast_strdupa(data);

	AST_STANDARD_APP_ARGS(args, s);


	if (!args.word1 || !args.word2 || !args.word5 || !args.num) {
		ast_log(LOG_WARNING, "SayCountPL requires 4 arguments: word-1,word-2,word-3,number\n");
		return -1;
	}

	if (sscanf(args.num, "%30d", &inum) != 1) {
		ast_log(LOG_WARNING, "'%s' is not a valid number\n", args.num);
		return -1;
	}


	res = saywords(chan, args.word1, args.word2, args.word5, inum);

	return res;
}
