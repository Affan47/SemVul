drbd_recv_all(struct drbd_connection *connection, void *buf, size_t size)
{
	int err;

	err = drbd_recv(connection, buf, size);
	if (err != size) {
		if (err >= 0)
			err = -EIO;
	} else
		err = 0;
	return err;
}
