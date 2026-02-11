main(int argc, char **argv) {
	int i, list = 0;
	const char *cfg = "/etc/ssl/https-proxy.conf";;

	for (i = 1; i < argc; ++i) {
		if (!strcmp(argv[i], "-c") && ++i < argc)
			cfg = argv[i];
		else if (!strcmp(argv[i], "-s3"))
			tls_only = 0;
		else if (!strcmp(argv[i], "-h"))
			return help();
		else if (!strcmp(argv[i], "-l"))
			list = 1;
		else {
			fprintf(stderr, "Unknown argument %s\n", argv[i]);
			return 1;
		}
	}

	init_context();
	if (!load_conf(cfg, list))
		return 1;
	if (list)
		return list_conf();
	listen_sock(server_port);
	if (use_uid && setuid(use_uid)) {
		fprintf(stderr, "setuid(%d): %s\n", use_uid, strerror(errno));
		return 1;
	}
	for (;;) {
		if (poll(ev, fd_count, -1) > 0) {
			after_poll();
		} else if (errno != EINTR) {
			perror("poll");
			break;
		}
	}
	free_context();
	return 0;
}
