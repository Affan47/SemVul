parse_cmd_option(const char *opt, const char *val,
		     struct fio_option *options, void *data)
{
	struct fio_option *o;

	o = find_option(options, opt);
	if (!o) {
		log_err("Bad option <%s>\n", opt);
		return 1;
	}

	if (!handle_option(o, val, data))
		return 0;

	log_err("fio: failed parsing %s=%s\n", opt, val);
	return 1;
}
