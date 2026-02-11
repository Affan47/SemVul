get_file(int s)
{
	int len;
	unsigned long filelen;
	struct timeval tv;
	char buffer2[1024];
	char buffer[1024];
	char buffer3[1024];
	progress_callback_data *pcd = calloc(1, sizeof(progress_callback_data));
	fd_set set;

	fd = accept(s, NULL, NULL);
	close(s);
	if (xfer_in_progress)
		return;
	xfer_in_progress = 1;

	FD_ZERO(&set);
	FD_SET(fd, &set);

	tv.tv_sec = 0;
	tv.tv_usec = 20;

	while (!select(fd + 1, &set, NULL, NULL, &tv)) {
		while (gtk_events_pending())
			gtk_main_iteration();
	}

	recv(fd, buffer, 5, 0);
	buffer[5] = 0;
	len = atoi(buffer);
	recv(fd, buffer2, len, 0);
	buffer2[len] = 0;
	recv(fd, &filelen, 4, 0);
	filelen = ntohl(filelen);

	snprintf(buffer, 1024, "Transferring %s...", buffer2);
	pcd->tag = ay_progress_bar_add(buffer, filelen, NULL, NULL);

	snprintf(buffer, 1024, "%s/%s", getenv("HOME"), buffer2);
	printf("receiving file %s\n", buffer);
	amount_received = 0;
	fp = fopen(buffer, "wb");

	snprintf(buffer3, 1024,
		_("Would you like to accept\n the file %s?\nSize=%lu"), buffer2,
		(unsigned long)filelen);
	eb_do_dialog(buffer3, _("Download File"), accept_file, pcd);
}
