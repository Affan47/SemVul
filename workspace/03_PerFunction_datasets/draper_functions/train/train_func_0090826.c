sbc_new(int op, char *path, char *capacity, char *media_type)
{
	int fd;

	if (!strncasecmp("disk", media_type, 4)) {
		uint32_t size;
		char *buf;

		sscanf(capacity, "%d", &size);
		if (size == 0) {
			printf("Capacity must be > 0\n");
			exit(3);
		}

		buf = malloc(1024*1024);
		if (buf == NULL) {
			printf("Failed to malloc buffer\n");
			exit(4);
		}
		fd = creat(path, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
		if (fd < 0) {
			perror("Failed creating file");
			exit(2);
		}
		if (posix_fallocate(fd, 0, size*1024*1024LL) == -1) {
			perror("posix_fallocate failed.");
			exit(3);
		}

		free(buf);
		close(fd);

		printf("Created blank DISK image file : %s\n", path);
		syslog(LOG_DAEMON|LOG_INFO, "DISK %s being created", path);
	} else {
		eprintf("unknown media type when creating disk\n");
		usage(1);
	}

	return 0;
}
