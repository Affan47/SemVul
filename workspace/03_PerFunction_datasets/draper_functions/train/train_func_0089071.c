check_key(struct wstate *ws)
{
	char buf[1024];
	int fd;
	int rd;
	struct timeval now;

	fd = open(KEY_FILE, O_RDONLY);

	if (fd == -1) {
		return;
	}

	rd = read(fd, buf, sizeof(buf) -1);
	if (rd == -1) {
		perror("read()");
		exit(1);
	}

	buf[rd] = 0;

	close(fd);

	printf ("\n\n");
	time_print("KEY=(%s)\n", buf);

	if (gettimeofday(&now, NULL) == -1) {
		perror("gettimeofday()");
		exit(1);
	}

	printf ("Owned in %.02f minutes\n",
		((double) now.tv_sec - ws->ws_real_start.tv_sec)/60.0);

	cleanup(0);
	exit(0);
}
