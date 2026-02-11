camel_movemail (const gchar *source,
                const gchar *dest,
                GError **error)
{
	gint lockid = -1;
	gint res = -1;
	gint sfd, dfd;
	struct stat st;


	if (g_stat (source, &st) == -1) {
		if (errno != ENOENT)
			g_set_error (
				error, G_IO_ERROR,
				g_io_error_from_errno (errno),
				_("Could not check mail file %s: %s"),
				source, g_strerror (errno));
		return -1;
	}

	if (st.st_size == 0)
		return 0;


	sfd = open (source, O_RDWR);
	if (sfd == -1) {
		g_set_error (
			error, G_IO_ERROR,
			g_io_error_from_errno (errno),
			_("Could not open mail file %s: %s"),
			source, g_strerror (errno));
		return -1;
	}

	dfd = open (dest, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (dfd == -1) {
		g_set_error (
			error, G_IO_ERROR,
			g_io_error_from_errno (errno),
			_("Could not open temporary mail file %s: %s"),
			dest, g_strerror (errno));
		close (sfd);
		return -1;
	}


	lockid = camel_lock_helper_lock (source, error);
	if (lockid == -1) {
		close (sfd);
		close (dfd);
		return -1;
	}

#ifdef HAVE_BROKEN_SPOOL
	res = camel_movemail_solaris (sfd, dfd, ex);
#else
	res = camel_movemail_copy_file (sfd, dfd, error);
#endif


	if (res != -1) {
		if (close (dfd) == 0) {
			ftruncate (sfd, 0);
		} else {
			g_set_error (
				error, G_IO_ERROR,
				g_io_error_from_errno (errno),
				_("Failed to store mail in temp file %s: %s"),
				dest, g_strerror (errno));
			res = -1;
		}
	} else
		close (dfd);
	close (sfd);

	camel_lock_helper_unlock (lockid);

	return res;
}
