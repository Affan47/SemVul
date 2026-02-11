cmd_send_pack(int argc, const char **argv, const char *prefix)
{
	int i, nr_heads = 0;
	const char **heads = NULL;
	const char *remote_name = NULL;
	struct remote *remote = NULL;
	const char *dest = NULL;

	argv++;
	for (i = 1; i < argc; i++, argv++) {
		const char *arg = *argv;

		if (*arg == '-') {
			if (!prefixcmp(arg, "--receive-pack=")) {
				args.receivepack = arg + 15;
				continue;
			}
			if (!prefixcmp(arg, "--exec=")) {
				args.receivepack = arg + 7;
				continue;
			}
			if (!prefixcmp(arg, "--remote=")) {
				remote_name = arg + 9;
				continue;
			}
			if (!strcmp(arg, "--all")) {
				args.send_all = 1;
				continue;
			}
			if (!strcmp(arg, "--dry-run")) {
				args.dry_run = 1;
				continue;
			}
			if (!strcmp(arg, "--mirror")) {
				args.send_mirror = 1;
				continue;
			}
			if (!strcmp(arg, "--force")) {
				args.force_update = 1;
				continue;
			}
			if (!strcmp(arg, "--verbose")) {
				args.verbose = 1;
				continue;
			}
			if (!strcmp(arg, "--thin")) {
				args.use_thin_pack = 1;
				continue;
			}
			usage(send_pack_usage);
		}
		if (!dest) {
			dest = arg;
			continue;
		}
		heads = (const char **) argv;
		nr_heads = argc - i;
		break;
	}
	if (!dest)
		usage(send_pack_usage);


	if ((heads && (args.send_all || args.send_mirror)) ||
					(args.send_all && args.send_mirror))
		usage(send_pack_usage);

	if (remote_name) {
		remote = remote_get(remote_name);
		if (!remote_has_url(remote, dest)) {
			die("Destination %s is not a uri for %s",
			    dest, remote_name);
		}
	}

	return send_pack(&args, dest, remote, nr_heads, heads);
}
