chunked_data_send(int dst, int src) {
	char *buf;
	int bsize;
	int i, w, csize;

	char *err = NULL;

	bsize = BUFSIZE;
	buf = new(bsize);


	do {
		i = so_recvln(src, &buf, &bsize);
		if (i <= 0) {
			if (debug)
				printf("chunked_data_send: aborting, read error\n");
			free(buf);
			return 0;
		}

		csize = strtol(buf, &err, 16);

		if (!isspace(*err) && *err != ';') {
			if (debug)
				printf("chunked_data_send: aborting, chunk size format error\n");
			free(buf);
			return 0;
		}

		if (dst >= 0)
			i = write(dst, buf, strlen(buf));

		if (csize)
			if (!data_send(dst, src, csize+2)) {
				if (debug)
					printf("chunked_data_send: aborting, data_send failed\n");

				free(buf);
				return 0;
			}
	} while (csize != 0);


	do {
		i = so_recvln(src, &buf, &bsize);
		if (dst >= 0 && i > 0)
			w = write(dst, buf, strlen(buf));
	} while (i > 0 && buf[0] != '\r' && buf[0] != '\n');

	free(buf);
	return 1;
}
