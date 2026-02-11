bfb_send_data(fd_t fd, uint8_t type, uint8_t *data, uint16_t length, uint8_t seq)
{
	uint8_t *buffer;
	int actual;

	buffer = malloc(length + 7);
	if (buffer == NULL)
		return -1;

	actual = bfb_stuff_data(buffer, type, data, length, seq);
	DEBUG(3, "%s() Stuffed %d bytes\n", __func__, actual);

	actual = bfb_write_packets(fd, BFB_FRAME_DATA, buffer, actual);
	DEBUG(3, "%s() Wrote %d packets\n", __func__, actual);

	free(buffer);

	return actual;
}
