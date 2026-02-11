msgport_sync_with_pipe (gint fd)
{
	gchar buffer[1];

	while (fd >= 0) {
		if (MP_READ (fd, buffer, 1) > 0)
			break;
		else if (!MP_IS_STATUS_INTR ()) {
			g_warning (
				"%s: Failed to read from pipe: %s",
				G_STRFUNC, g_strerror (errno));
			break;
		}
	}
}
