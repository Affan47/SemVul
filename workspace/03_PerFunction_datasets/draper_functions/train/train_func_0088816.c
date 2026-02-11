revert_or_cherry_pick(int argc, const char **argv)
{
	struct rev_info revs;

	git_config(git_default_config, NULL);
	me = action == REVERT ? "revert" : "cherry-pick";
	setenv(GIT_REFLOG_ACTION, me, 0);
	parse_args(argc, argv);

	if (allow_ff) {
		if (signoff)
			die("cherry-pick --ff cannot be used with --signoff");
		if (no_commit)
			die("cherry-pick --ff cannot be used with --no-commit");
		if (no_replay)
			die("cherry-pick --ff cannot be used with -x");
		if (edit)
			die("cherry-pick --ff cannot be used with --edit");
	}

	read_and_refresh_cache(me);

	prepare_revs(&revs);

	while ((commit = get_revision(&revs))) {
		int res = do_pick_commit();
		if (res)
			return res;
	}

	return 0;
}
