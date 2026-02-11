control_connect (const gchar *path,
                 GkdControlFlags flags)
{
	struct sockaddr_un addr;
	struct stat st;
	int sock;


	if (lstat (path, &st) < 0) {
		if (!(flags & GKD_CONTROL_QUIET_IF_NO_PEER) || errno != ENOENT)
			g_message ("couldn't access control socket: %s: %s", path, g_strerror (errno));
		return -1;

	} else if (st.st_uid != geteuid ()) {
		g_message("The control socket is not owned with the same "
		          "credentials as the user login: %s", path);
		return -1;

	} else if (S_ISLNK (st.st_mode) || !S_ISSOCK (st.st_mode)) {
		g_message ("The control socket is not a valid simple non-linked socket");
		return -1;
	}

	addr.sun_family = AF_UNIX;
	g_strlcpy (addr.sun_path, path, sizeof (addr.sun_path));


	sock = socket (AF_UNIX, SOCK_STREAM, 0);
	if (sock < 0) {
		g_warning ("couldn't create control socket: %s", g_strerror (errno));
		return -1;
	}


	fcntl (sock, F_SETFD, 1);

	if (connect (sock, (struct sockaddr*) &addr, sizeof (addr)) < 0) {
		if (!(flags & GKD_CONTROL_QUIET_IF_NO_PEER) || errno != ECONNREFUSED)
			g_message ("couldn't connect to control socket at: %s: %s",
			           addr.sun_path, g_strerror (errno));
		close (sock);
		return -1;
	}


	for (;;) {
		if (egg_unix_credentials_write (sock) < 0) {
			if (errno == EINTR || errno == EAGAIN)
				continue;
			g_message ("couldn't send credentials to control socket: %s",
			           g_strerror (errno));
			close (sock);
			return -1;
		}

		return sock;
	}
}
