fetch_one(struct remote *remote, int argc, const char **argv)
{
	int i;
	static const char **refs = NULL;
	int ref_nr = 0;
	int exit_code;

	if (!remote)
		die(_("No remote repository specified.  Please, specify either a URL or a\n"
		    "remote name from which new revisions should be fetched."));

	transport = transport_get(remote, NULL);
	transport_set_verbosity(transport, verbosity, progress);
	if (upload_pack)
		set_option(TRANS_OPT_UPLOADPACK, upload_pack);
	if (keep)
		set_option(TRANS_OPT_KEEP, "yes");
	if (depth)
		set_option(TRANS_OPT_DEPTH, depth);

	if (argc > 0) {
		int j = 0;
		refs = xcalloc(argc + 1, sizeof(const char *));
		for (i = 0; i < argc; i++) {
			if (!strcmp(argv[i], "tag")) {
				char *ref;
				i++;
				if (i >= argc)
					die(_("You need to specify a tag name."));
				ref = xmalloc(strlen(argv[i]) * 2 + 22);
				strcpy(ref, "refs/tags/");
				strcat(ref, argv[i]);
				strcat(ref, ":refs/tags/");
				strcat(ref, argv[i]);
				refs[j++] = ref;
			} else
				refs[j++] = argv[i];
		}
		refs[j] = NULL;
		ref_nr = j;
	}

	sigchain_push_common(unlock_pack_on_signal);
	atexit(unlock_pack);
	exit_code = do_fetch(transport,
			parse_fetch_refspec(ref_nr, refs), ref_nr);
	transport_disconnect(transport);
	transport = NULL;
	return exit_code;
}
