au_opts_parse_del(struct au_opt_del *del, substring_t args[])
{
	int err;

	del->pathname = args[0].from;
	AuDbg("del path %s\n", del->pathname);

	err = vfsub_kern_path(del->pathname, lkup_dirflags, &del->h_path);
	if (unlikely(err))
		pr_err("lookup failed %s (%d)\n", del->pathname, err);

	return err;
}
