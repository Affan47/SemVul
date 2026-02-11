prune(int argc, const char **argv)
{
	int dry_run = 0, result = 0;
	struct option options[] = {
		OPT_GROUP("prune specific options"),
		OPT__DRY_RUN(&dry_run),
		OPT_END()
	};
	struct ref_states states;

	argc = parse_options(argc, argv, options, builtin_remote_usage, 0);

	if (argc < 1)
		usage_with_options(builtin_remote_usage, options);

	memset(&states, 0, sizeof(states));
	for (; argc; argc--, argv++) {
		int i;

		get_remote_ref_states(*argv, &states, 1);

		if (states.stale.nr) {
			printf("Pruning %s\n", *argv);
			printf("URL: %s\n",
			       states.remote->url_nr
			       ? states.remote->url[0]
			       : "(no URL)");
		}

		for (i = 0; i < states.stale.nr; i++) {
			const char *refname = states.stale.items[i].util;

			if (!dry_run)
				result |= delete_ref(refname, NULL);

			printf(" * [%s] %s\n", dry_run ? "would prune" : "pruned",
			       abbrev_ref(refname, "refs/remotes/"));
		}


		string_list_clear(&states.new, 0);
		string_list_clear(&states.stale, 0);
		string_list_clear(&states.tracked, 0);
	}

	return result;
}
