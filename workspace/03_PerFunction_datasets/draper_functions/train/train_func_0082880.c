e_file_lock_destroy (void)
{
	const gchar *filename = get_lock_filename ();

	if (g_unlink (filename) == -1) {
		const gchar *errmsg = g_strerror (errno);
		g_warning ("Lock file deletion failed: %s", errmsg);
	}
}
