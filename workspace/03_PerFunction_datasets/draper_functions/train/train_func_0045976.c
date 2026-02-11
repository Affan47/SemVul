main(int argc, const char **argv)
{
	const char *path;
	char *qry;
	int err, ttl;
	const char * const iis = getenv("USING_IIS");


	if((iis != NULL) && (*iis == 'Y'))
		freopen("/dev/null", "w", stderr);

	git_extract_argv0_path(argv[0]);

	prepare_context(&ctx);
	cgit_repolist.length = 0;
	cgit_repolist.count = 0;
	cgit_repolist.repos = NULL;

	cgit_parse_args(argc, argv);
	parse_configfile(ctx.env.cgit_config, config_cb);
	ctx.repo = NULL;
	http_parse_querystring(ctx.qry.raw, querystring_cb);


	if (!ctx.cfg.virtual_root)
		ctx.cfg.virtual_root = ctx.cfg.script_name;


	path = ctx.env.path_info;
	if (!ctx.qry.url && path) {
		if (path[0] == '/')
			path++;
		ctx.qry.url = xstrdup(path);
		if (ctx.qry.raw) {
			qry = ctx.qry.raw;
			ctx.qry.raw = xstrdup(fmt("%s?%s", path, qry));
			free(qry);
		} else
			ctx.qry.raw = xstrdup(ctx.qry.url);
		cgit_parse_url(ctx.qry.url);
	}

	ttl = calc_ttl();
	ctx.page.expires += ttl*60;
	if (ctx.env.request_method && !strcmp(ctx.env.request_method, "HEAD"))
		ctx.cfg.nocache = 1;
	if (ctx.cfg.nocache)
		ctx.cfg.cache_size = 0;
	err = cache_process(ctx.cfg.cache_size, ctx.cfg.cache_root,
			    ctx.qry.raw, ttl, process_request, &ctx);
	if (err)
		cgit_print_error(fmt("Error processing page: %s (%d)",
				     strerror(err), err));
	return err;
}
