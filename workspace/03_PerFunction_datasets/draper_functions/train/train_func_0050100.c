write_credentials_byte (int sock)
{
	for (;;) {
		if (egg_unix_credentials_write (sock) < 0) {
			if (errno == EINTR || errno == EAGAIN)
				continue;
			syslog (GKR_LOG_ERR, "couldn't send credentials to daemon: %s",
			        strerror (errno));
			return -1;
		}

		break;
	}

	return 0;
}
