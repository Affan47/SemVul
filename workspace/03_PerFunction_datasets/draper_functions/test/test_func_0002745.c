free_attachment (struct attachment *attachment)
{
	if (!attachment)
		return;

	icalattach_unref (attachment->attach);

	if (attachment->temporary_filename) {
		gchar *sep;

		g_unlink (attachment->temporary_filename);

		sep = strrchr (attachment->temporary_filename, G_DIR_SEPARATOR);
		if (sep) {
			*sep = '\0';
			g_rmdir (attachment->temporary_filename);
		}
	}

	g_free (attachment->temporary_filename);
	g_free (attachment);
}
