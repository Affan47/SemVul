cgit_parse_args(int argc, const char **argv)
{
	int i;
	int scan = 0;

	for (i = 1; i < argc; i++) {
		if (!strncmp(argv[i], "--cache=", 8)) {
			ctx.cfg.cache_root = xstrdup(argv[i]+8);
		}
		if (!strcmp(argv[i], "--nocache")) {
			ctx.cfg.nocache = 1;
		}
		if (!strcmp(argv[i], "--nohttp")) {
			ctx.env.no_http = "1";
		}
		if (!strncmp(argv[i], "--query=", 8)) {
			ctx.qry.raw = xstrdup(argv[i]+8);
		}
		if (!strncmp(argv[i], "--repo=", 7)) {
			ctx.qry.repo = xstrdup(argv[i]+7);
		}
		if (!strncmp(argv[i], "--page=", 7)) {
			ctx.qry.page = xstrdup(argv[i]+7);
		}
		if (!strncmp(argv[i], "--head=", 7)) {
			ctx.qry.head = xstrdup(argv[i]+7);
			ctx.qry.has_symref = 1;
		}
		if (!strncmp(argv[i], "--sha1=", 7)) {
			ctx.qry.sha1 = xstrdup(argv[i]+7);
			ctx.qry.has_sha1 = 1;
		}
		if (!strncmp(argv[i], "--ofs=", 6)) {
			ctx.qry.ofs = atoi(argv[i]+6);
		}
		if (!strncmp(argv[i], "--scan-tree=", 12) ||
		    !strncmp(argv[i], "--scan-path=", 12)) {


			ctx.cfg.snapshots = 0xFF;
			scan++;
			scan_tree(argv[i] + 12, repo_config);
		}
	}
	if (scan) {
		qsort(cgit_repolist.repos, cgit_repolist.count,
			sizeof(struct cgit_repo), cmp_repos);
		print_repolist(stdout, &cgit_repolist, 0);
		exit(0);
	}
}
