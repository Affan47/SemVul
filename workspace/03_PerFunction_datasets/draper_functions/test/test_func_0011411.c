cmd_fmt_merge_msg(int argc, const char **argv, const char *prefix)
{
	const char *inpath = NULL;
	const char *message = NULL;
	struct option options[] = {
		{ OPTION_INTEGER, 0, "log", &shortlog_len, "n",
		  "populate log with at most <n> entries from shortlog",
		  PARSE_OPT_OPTARG, NULL, DEFAULT_MERGE_LOG_LEN },
		{ OPTION_INTEGER, 0, "summary", &shortlog_len, "n",
		  "alias for --log (deprecated)",
		  PARSE_OPT_OPTARG | PARSE_OPT_HIDDEN, NULL,
		  DEFAULT_MERGE_LOG_LEN },
		OPT_STRING('m', "message", &message, "text",
			"use <text> as start of message"),
		OPT_FILENAME('F', "file", &inpath, "file to read from"),
		OPT_END()
	};

	FILE *in = stdin;
	struct strbuf input = STRBUF_INIT, output = STRBUF_INIT;
	int ret;

	git_config(fmt_merge_msg_config, NULL);
	argc = parse_options(argc, argv, prefix, options, fmt_merge_msg_usage,
			     0);
	if (argc > 0)
		usage_with_options(fmt_merge_msg_usage, options);
	if (message && !shortlog_len) {
		char nl = '\n';
		write_in_full(STDOUT_FILENO, message, strlen(message));
		write_in_full(STDOUT_FILENO, &nl, 1);
		return 0;
	}
	if (shortlog_len < 0)
		die("Negative --log=%d", shortlog_len);

	if (inpath && strcmp(inpath, "-")) {
		in = fopen(inpath, "r");
		if (!in)
			die_errno("cannot open '%s'", inpath);
	}

	if (strbuf_read(&input, fileno(in), 0) < 0)
		die_errno("could not read input file");

	if (message)
		strbuf_addstr(&output, message);
	ret = fmt_merge_msg(&input, &output,
			    message ? 0 : 1,
			    shortlog_len);

	if (ret)
		return ret;
	write_in_full(STDOUT_FILENO, output.buf, output.len);
	return 0;
}
