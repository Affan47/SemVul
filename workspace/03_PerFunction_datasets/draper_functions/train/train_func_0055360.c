usbmuxd_send(int sfd, const char *data, uint32_t len, uint32_t *sent_bytes)
{
	int num_sent;

	if (sfd < 0) {
		return -EINVAL;
	}

	num_sent = send(sfd, (void*)data, len, 0);
	if (num_sent < 0) {
		*sent_bytes = 0;
		fprintf(stderr, "%s: Error %d when sending: %s\n", __func__, num_sent, strerror(errno));
		return num_sent;
	} else if ((uint32_t)num_sent < len) {
		fprintf(stderr, "%s: Warning: Did not send enough (only %d of %d)\n", __func__, num_sent, len);
	}

	*sent_bytes = num_sent;

	return 0;
}
