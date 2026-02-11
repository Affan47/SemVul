xmms_ipc_usocket_server_init (const xmms_url_t *url)
{
	int fd;
	int flags;
	xmms_ipc_transport_t *ipct;
	struct sockaddr_un saddr;


	fd = socket (AF_UNIX, SOCK_STREAM, 0);
	if (fd == -1) {
		return NULL;
	}

	saddr.sun_family = AF_UNIX;
	snprintf (saddr.sun_path, sizeof (saddr.sun_path), "/%s", url->path);

	if (access (saddr.sun_path, F_OK) == 0) {
		if (connect (fd, (struct sockaddr *) &saddr, sizeof (saddr)) != -1) {

			close (fd);
			return NULL;
		}

		unlink (saddr.sun_path);
	}

	if (bind (fd, (struct sockaddr *) &saddr, sizeof (saddr)) == -1) {
		close (fd);
		return NULL;
	}

	listen (fd, 5);

	flags = fcntl (fd, F_GETFL, 0);

	if (flags == -1) {
		close (fd);
		return NULL;
	}

	flags |= O_NONBLOCK;

	flags = fcntl (fd, F_SETFL, flags);
	if (flags == -1) {
		close (fd);
		return NULL;
	}

	ipct = x_new0 (xmms_ipc_transport_t, 1);
	ipct->fd = fd;
	ipct->path = strdup (url->path);
	ipct->read_func = xmms_ipc_usocket_read;
	ipct->write_func = xmms_ipc_usocket_write;
	ipct->accept_func = xmms_ipc_usocket_accept;
	ipct->destroy_func = xmms_ipc_usocket_destroy;

	return ipct;
}
