brf_send_command_file(int fd, struct bts_action_send* send_action, long size)
{
	unsigned char response[1024] = {0};
	long ret = 0;


	if (size != write(fd, send_action, size)) {
		perror("Texas: Failed to write action command");
		return -1;
	}


	ret = read_hci_event(fd, response, sizeof(response));
	if (ret < 0) {
		perror("texas: failed to read command response");
		return -1;
	}


	if (ret < 7 || 0 != response[6]) {
		fprintf( stderr, "TI init command failed.\n" );
		errno = EIO;
		return -1;
	}

	return 0;
}
