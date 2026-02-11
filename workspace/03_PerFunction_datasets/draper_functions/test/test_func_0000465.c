file_count_line(struct ast_channel *chan, const char *cmd, char *data, struct ast_str **buf, ssize_t len)
{
	enum file_format newline_format = FF_UNKNOWN;
	int64_t count;
	AST_DECLARE_APP_ARGS(args,
		AST_APP_ARG(filename);
		AST_APP_ARG(format);
	);

	AST_STANDARD_APP_ARGS(args, data);
	if (args.argc > 1) {
		if (tolower(args.format[0]) == 'd') {
			newline_format = FF_DOS;
		} else if (tolower(args.format[0]) == 'm') {
			newline_format = FF_MAC;
		} else if (tolower(args.format[0]) == 'u') {
			newline_format = FF_UNIX;
		}
	}

	count = count_lines(args.filename, newline_format);
	ast_str_set(buf, len, "%" PRId64, count);
	return 0;
}
