bfb_write_packets(fd_t fd, uint8_t type, uint8_t *buffer, int length)
{
	bfb_frame_t *frame;
	int i;
	int l;

	struct timeval timeout;
	fd_set fds;
	int rc;
#ifdef _WIN32
	DWORD actual;
#else
	int actual;
#endif

#ifdef _WIN32
        return_val_if_fail (fd != INVALID_HANDLE_VALUE, FALSE);
#else
        return_val_if_fail (fd > 0, FALSE);
#endif

	FD_ZERO(&fds);
	FD_SET(fd, &fds);


	frame = malloc((length > MAX_PACKET_DATA ? MAX_PACKET_DATA : length) + sizeof (bfb_frame_t));
	if (frame == NULL)
		return -1;

	for(i=0; i <length; i += MAX_PACKET_DATA) {

		l = length - i;
		if (l > MAX_PACKET_DATA)
			l = MAX_PACKET_DATA;

		frame->type = type;
		frame->len = l;
		frame->chk = frame->type ^ frame->len;

		memcpy(frame->payload, &buffer[i], l);


		timeout.tv_sec = 1;
		timeout.tv_usec = 0;


		rc = select(fd+1, NULL, &fds, NULL, &timeout);
		if ( rc > 0) {
#ifdef _WIN32
			if(!WriteFile(fd, frame, l + sizeof (bfb_frame_t), &actual, NULL))
				DEBUG(2, "%s() Write error: %ld\n", __func__, actual);
			DEBUG(3, "%s() Wrote %ld bytes (expected %d)\n", __func__, actual, l + sizeof (bfb_frame_t));
#else
			actual = write(fd, frame, l + sizeof (bfb_frame_t));
			DEBUG(3, "%s() Wrote %d bytes (expected %d)\n", __func__, actual, l + sizeof (bfb_frame_t));


#endif
			if (actual < 0 || actual < l + (int) sizeof (bfb_frame_t)) {
				DEBUG(1, "%s() Write failed\n", __func__);
				free(frame);
				return -1;
			}
		} else {
			DEBUG(1, "%s() Select failed\n", __func__);
			free(frame);
			return -1;
		}

	}
	free(frame);
	return i / MAX_PACKET_DATA;
}
