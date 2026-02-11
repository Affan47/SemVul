parse_option(char *opt, const char *input,
		 struct fio_option *options, struct fio_option **o, void *data,
		 int dump_cmdline)
{
	char *post;

	if (!opt) {
		log_err("fio: failed parsing %s\n", input);
		*o = NULL;
		return 1;
	}

	*o = get_option(opt, options, &post);
	if (!*o) {
		if (post) {
			int len = strlen(opt);
			if (opt + len + 1 != post)
				memmove(opt + len + 1, post, strlen(post));
			opt[len] = '=';
		}
		return 1;
	}

	if (handle_option(*o, post, data)) {
		log_err("fio: failed parsing %s\n", input);
		return 1;
	}

	if (dump_cmdline) {
		const char *delim;

		if (!strcmp("description", (*o)->name))
			delim = "\"";
		else
			delim = "";

		log_info("--%s%s", (*o)->name, post ? "" : " ");
		if (post)
			log_info("=%s%s%s ", delim, post, delim);
	}

	return 0;
}
