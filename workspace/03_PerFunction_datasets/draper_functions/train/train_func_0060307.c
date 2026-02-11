netns_exec(int argc, char **argv)
{


	const char *name, *cmd;
	char net_path[MAXPATHLEN];
	int netns;

	if (argc < 1) {
		fprintf(stderr, "No netns name specified\n");
		return -1;
	}
	if (argc < 2) {
		fprintf(stderr, "No command specified\n");
		return -1;
	}

	name = argv[0];
	cmd = argv[1];
	snprintf(net_path, sizeof(net_path), "%s/%s", NETNS_RUN_DIR, name);
	netns = open(net_path, O_RDONLY | O_CLOEXEC);
	if (netns < 0) {
		fprintf(stderr, "Cannot open network namespace \"%s\": %s\n",
			name, strerror(errno));
		return -1;
	}

	if (setns(netns, CLONE_NEWNET) < 0) {
		fprintf(stderr, "seting the network namespace \"%s\" failed: %s\n",
			name, strerror(errno));
		return -1;
	}

	if (unshare(CLONE_NEWNS) < 0) {
		fprintf(stderr, "unshare failed: %s\n", strerror(errno));
		return -1;
	}

	if (mount("", "/", "none", MS_SLAVE | MS_REC, NULL)) {
		fprintf(stderr, "\"mount --make-rslave /\" failed: %s\n",
			strerror(errno));
		return -1;
	}

	if (umount2("/sys", MNT_DETACH) < 0) {
		fprintf(stderr, "umount of /sys failed: %s\n", strerror(errno));
		return -1;
	}
	if (mount(name, "/sys", "sysfs", 0, NULL) < 0) {
		fprintf(stderr, "mount of /sys failed: %s\n",strerror(errno));
		return -1;
	}


	bind_etc(name);

	fflush(stdout);

	if (batch_mode) {
		int status;
		pid_t pid;

		pid = fork();
		if (pid < 0) {
			perror("fork");
			exit(1);
		}

		if (pid != 0) {

			if (waitpid(pid, &status, 0) < 0) {
				perror("waitpid");
				exit(1);
			}

			if (WIFEXITED(status)) {


				return -WEXITSTATUS(status);
			}

			exit(1);
		}
	}

	if (execvp(cmd, argv + 1)  < 0)
		fprintf(stderr, "exec of \"%s\" failed: %s\n",
			cmd, strerror(errno));
	_exit(1);
}
