lock_and_open_file (const gchar *filename,
                    gint flags)
{
	dotlock_t lockh;
	gint fd = -1;


	fd = open (filename, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		g_message ("couldn't open store file: %s: %s",
		           filename, g_strerror (errno));
		return NULL;
	}

	lockh = dotlock_create (filename, 0);
	if (!lockh) {
		g_message ("couldn't create lock for store file: %s: %s",
		           filename, g_strerror (errno));
		close (fd);
		return NULL;
	}

	if (dotlock_take (lockh, LOCK_TIMEOUT)) {
		if (errno == EACCES)
			g_message ("couldn't write to store file:"
			           " %s: file is locked", filename);
		else
			g_message ("couldn't lock store file: %s: %s",
			           filename, g_strerror (errno));
		dotlock_destroy (lockh);
		close (fd);
		return NULL;
	}

	;
	dotlock_set_fd (lockh, fd);
	return lockh;
}
