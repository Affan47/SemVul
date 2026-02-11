net_receive(GIOChannel *handle, char *buf, int len)
{
        gsize ret;
	int err;

	g_return_val_if_fail(handle != NULL, -1);
	g_return_val_if_fail(buf != NULL, -1);

	err = g_io_channel_read(handle, buf, len, &ret);
	if (err == 0 && ret == 0)
		return -1;

	if (err == G_IO_ERROR_AGAIN || (err != 0 && errno == EINTR))
		return 0;

	return err == 0 ? (int)ret : -1;
}
