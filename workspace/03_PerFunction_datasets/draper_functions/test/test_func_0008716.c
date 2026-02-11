sstate_connect(void)
{
	int	ret, fd;
	const char	*dumpcmd = "DUMPALL\n";
	struct sockaddr_un	sa;

	memset(&sa, '\0', sizeof(sa));
	sa.sun_family = AF_UNIX;
	snprintf(sa.sun_path, sizeof(sa.sun_path), "%s/%s", dflt_statepath(), device_path);

	fd = socket(AF_UNIX, SOCK_STREAM, 0);

	if (fd < 0) {
		upslog_with_errno(LOG_ERR, "Can't create socket for UPS [%s]", device_path);
		return -1;
	}

	ret = connect(fd, (struct sockaddr *) &sa, sizeof(sa));

	if (ret < 0) {
		time_t	now;

		close(fd);


		time(&now);

		if (difftime(now, last_connfail) < 60) {
			return -1;
		}

		last_connfail = now;

		upslog_with_errno(LOG_ERR, "Can't connect to UPS [%s]", device_path);
		return -1;
	}

	ret = fcntl(fd, F_GETFL, 0);

	if (ret < 0) {
		upslog_with_errno(LOG_ERR, "fcntl get on UPS [%s] failed", device_path);
		close(fd);
		return -1;
	}

	ret = fcntl(fd, F_SETFL, ret | O_NDELAY);

	if (ret < 0) {
		upslog_with_errno(LOG_ERR, "fcntl set O_NDELAY on UPS [%s] failed", device_path);
		close(fd);
		return -1;
	}


	ret = write(fd, dumpcmd, strlen(dumpcmd));

	if (ret != (int)strlen(dumpcmd)) {
		upslog_with_errno(LOG_ERR, "Initial write to UPS [%s] failed", device_path);
		close(fd);
		return -1;
	}

	pconf_init(&sock_ctx, NULL);

	time(&last_heard);

	dumpdone = 0;


	dstate_setinfo("ups.status", "WAIT");

	upslogx(LOG_INFO, "Connected to UPS [%s]", device_path);
	return fd;
}
