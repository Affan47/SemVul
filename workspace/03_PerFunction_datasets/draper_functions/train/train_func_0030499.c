compatible_revision(const char *name, uint8_t revision, int opt)
{
	struct xt_get_revision rev;
	socklen_t s = sizeof(rev);
	int max_rev, sockfd;

	sockfd = socket(afinfo->family, SOCK_RAW, IPPROTO_RAW);
	if (sockfd < 0) {
		if (errno == EPERM) {

			if (revision != 0)
				fprintf(stderr, "%s: Could not determine whether "
						"revision %u is supported, "
						"assuming it is.\n",
					name, revision);
			return 1;
		}
		fprintf(stderr, "Could not open socket to kernel: %s\n",
			strerror(errno));
		exit(1);
	}

	if (fcntl(sockfd, F_SETFD, FD_CLOEXEC) == -1) {
		fprintf(stderr, "Could not set close on exec: %s\n",
			strerror(errno));
		exit(1);
	}

	xtables_load_ko(xtables_modprobe_program, true);

	strcpy(rev.name, name);
	rev.revision = revision;

	max_rev = getsockopt(sockfd, afinfo->ipproto, opt, &rev, &s);
	if (max_rev < 0) {

		if (errno == ENOENT || errno == EPROTONOSUPPORT) {
			close(sockfd);
			return 0;
		} else if (errno == ENOPROTOOPT) {
			close(sockfd);

			return (revision == 0);
		} else {
			fprintf(stderr, "getsockopt failed strangely: %s\n",
				strerror(errno));
			exit(1);
		}
	}
	close(sockfd);
	return 1;
}
