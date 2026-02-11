netinfo_is_ipv6_enable (void)
{
	gint sock;
	struct sockaddr_in6 sin6;
	guint len;

	if ((sock = socket (PF_INET6, SOCK_STREAM, 0)) == -1) {
		return FALSE;
	} else {
		len = sizeof (struct sockaddr_in6);
		if (getsockname (sock, (struct sockaddr *)&sin6, (void *)&len) < 0) {
			close (sock);
			return FALSE;
		} else {
			close (sock);
			return TRUE;
		}
	}
}
