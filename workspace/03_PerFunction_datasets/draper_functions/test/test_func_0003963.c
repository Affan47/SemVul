main(int argc, char *argv[])
{
	const struct command *cmd, *best;
	int n;

	argv++;
	argc--;

	if (argc == 0)
		format();


	best = NULL;
	n = strlen(*argv);

	for (cmd = commands; cmd->action; cmd++) {
		if (memcmp(cmd->name, *argv, n) != 0)
			continue;

		if (cmd->name[n] == 0) {

			best = cmd;
			break;
		}


		if (best) {
			fprintf(stderr, "Ambiguous command\n");
			exit(2);
		}

		best = cmd;
	}

	if (!best) {
		fprintf(stderr, "Unknown command\n");
		exit(2);
	}


	myuid = geteuid();
	mygid = getegid();
	myngroups = getgroups(0, NULL);

	if (myuid == -1 || mygid == -1 || myngroups == -1)
		error("Unable to get UID/GID/#Groups\n");

	mygroups = calloc(myngroups, sizeof(gid_t));
	if (!mygroups)
		error("calloc");

	myngroups = getgroups(myngroups, mygroups);
	if (myngroups < 0)
		error("Unable to get Groups\n");

	return best->action(argc, argv);

}
