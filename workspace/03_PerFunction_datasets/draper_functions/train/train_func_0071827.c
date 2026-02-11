main(int argc, char **argv)
{
	int i, nr_heads = 0;
	char *dest = NULL;
	char **heads = NULL;
	int fd[2], ret;
	pid_t pid;
	char *remote_name = NULL;
	struct remote *remote = NULL;

	setup_git_directory();
	git_config(git_default_config);

	argv++;
	for (i = 1; i < argc; i++, argv++) {
		char *arg = *argv;

		if (*arg == '-') {
			if (!prefixcmp(arg, "--receive-pack=")) {
				receivepack = arg + 15;
				continue;
			}
			if (!prefixcmp(arg, "--exec=")) {
				receivepack = arg + 7;
				continue;
			}
			if (!prefixcmp(arg, "--remote=")) {
				remote_name = arg + 9;
				continue;
			}
			if (!strcmp(arg, "--all")) {
				send_all = 1;
				continue;
			}
			if (!strcmp(arg, "--force")) {
				force_update = 1;
				continue;
			}
			if (!strcmp(arg, "--verbose")) {
				verbose = 1;
				continue;
			}
			if (!strcmp(arg, "--thin")) {
				use_thin_pack = 1;
				continue;
			}
			usage(send_pack_usage);
		}
		if (!dest) {
			dest = arg;
			continue;
		}
		heads = argv;
		nr_heads = argc - i;
		break;
	}
	if (!dest)
		usage(send_pack_usage);
	if (heads && send_all)
		usage(send_pack_usage);
	verify_remote_names(nr_heads, heads);

	if (remote_name) {
		remote = remote_get(remote_name);
		if (!remote_has_uri(remote, dest)) {
			die("Destination %s is not a uri for %s",
			    dest, remote_name);
		}
	}

	pid = git_connect(fd, dest, receivepack, verbose ? CONNECT_VERBOSE : 0);
	if (pid < 0)
		return 1;
	ret = send_pack(fd[0], fd[1], remote, nr_heads, heads);
	close(fd[0]);
	close(fd[1]);
	ret |= finish_connect(pid);
	return !!ret;
}
