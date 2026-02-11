iscsi_service(struct iscsi_context *iscsi, int revents)
{
	if (revents & POLLERR) {
		printf("iscsi_service: POLLERR, socket error\n");
		iscsi->connect_cb(iscsi, ISCSI_STATUS_ERROR, NULL, iscsi->connect_data);
		return -1;
	}
	if (revents & POLLHUP) {
		printf("iscsi_service: POLLHUP, socket error\n");
		iscsi->connect_cb(iscsi, ISCSI_STATUS_ERROR, NULL, iscsi->connect_data);
		return -2;
	}

	if (iscsi->is_connected == 0 && iscsi->fd != -1 && revents&POLLOUT) {
		iscsi->is_connected = 1;
		iscsi->connect_cb(iscsi, ISCSI_STATUS_GOOD, NULL, iscsi->connect_data);
		return 0;
	}

	if (revents & POLLOUT && iscsi->outqueue != NULL) {
		if (iscsi_write_to_socket(iscsi) != 0) {
			printf("write to socket failed\n");
			return -3;
		}
	}
	if (revents & POLLIN) {
		if (iscsi_read_from_socket(iscsi) != 0) {
			printf("read from socket failed\n");
			return -4;
		}
	}

	return 0;
}
