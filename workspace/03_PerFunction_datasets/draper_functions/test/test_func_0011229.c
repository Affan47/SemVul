cmd_mailinfo(int argc, const char **argv, const char *prefix)
{
	const char *def_charset;


	git_config(git_default_config);

	def_charset = (git_commit_encoding ? git_commit_encoding : "utf-8");
	metainfo_charset = def_charset;

	while (1 < argc && argv[1][0] == '-') {
		if (!strcmp(argv[1], "-k"))
			keep_subject = 1;
		else if (!strcmp(argv[1], "-u"))
			metainfo_charset = def_charset;
		else if (!strcmp(argv[1], "-n"))
			metainfo_charset = NULL;
		else if (!prefixcmp(argv[1], "--encoding="))
			metainfo_charset = argv[1] + 11;
		else
			usage(mailinfo_usage);
		argc--; argv++;
	}

	if (argc != 3)
		usage(mailinfo_usage);

	return !!mailinfo(stdin, stdout, keep_subject, metainfo_charset, argv[1], argv[2]);
}
