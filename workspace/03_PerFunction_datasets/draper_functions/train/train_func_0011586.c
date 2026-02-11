remote_connect2(int fd, const char *password) {
#ifdef HAVE_SSL
	if (ssl_session) {
		watch_t *w;

		watch_add(NULL, fd, WATCH_READ, remote_read_ssl, string_init(NULL));
		w = watch_add_line(NULL, fd, WATCH_WRITE_LINE, remote_write_ssl, NULL);
		w->data = w->buf;
	} else
#endif
	{
		watch_t *w;

		watch_add_line(NULL, fd, WATCH_READ, remote_read, string_init(NULL));
		w = watch_add_line(NULL, fd, WATCH_WRITE_LINE, remote_write, NULL);
		w->data = w->buf;
	}


	remote_writefd(fd, "REQLOGIN", password, NULL);

	while (!login_OK)
		ekg_loop();

	if (login_OK != 1) {
		close(fd);
		errno = EACCES;
		return 0;
	}

	remote_writefd(fd, "REQCONFIG", NULL);

	while (!variables_OK)
		ekg_loop();
	remote_recode_reinit();

	remote_writefd(fd, "REQCOMMANDS", NULL);
	remote_writefd(fd, "REQFORMATS", NULL);
	remote_writefd(fd, "REQPLUGINS", NULL);
	remote_writefd(fd, "REQSESSIONS", NULL);
	remote_writefd(fd, "REQWINDOWS", NULL);
	remote_writefd(fd, "REQUSERLISTS", NULL);

	while (!commands_OK || !formats_OK || !plugins_OK || !sessions_OK || !windows_OK || !userlist_OK)
		ekg_loop();

	remote_fd = fd;

	return 1;
}
