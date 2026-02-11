received_udp_data(GIOChannel *channel, GIOCondition cond,
							gpointer user_data)
{
	struct resolv_nameserver *nameserver = user_data;
	unsigned char buf[4096];
	int sk, len;

	if (cond & (G_IO_NVAL | G_IO_ERR | G_IO_HUP)) {
		nameserver->udp_watch = 0;
		return FALSE;
	}

	sk = g_io_channel_unix_get_fd(nameserver->udp_channel);

	len = recv(sk, buf, sizeof(buf), 0);
	if (len < 12)
		return TRUE;

	parse_response(nameserver, buf, len);

	return TRUE;
}
