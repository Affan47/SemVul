send_message(struct sap_connection *conn, void *buf, size_t size)
{
	size_t written = 0;
	GError *gerr = NULL;
	GIOStatus gstatus;

	if (!conn || !buf)
		return -EINVAL;

	DBG("conn %p, size %zu", conn, size);

	gstatus = g_io_channel_write_chars(conn->io, buf, size, &written,
									&gerr);
	if (gstatus != G_IO_STATUS_NORMAL) {
		if (gerr)
			g_error_free(gerr);

		error("write error (0x%02x).", gstatus);
		return -EIO;
	}

	if (written != size) {
		error("written %zu bytes out of %zu", written, size);
		return -EIO;
	}

	return written;
}
