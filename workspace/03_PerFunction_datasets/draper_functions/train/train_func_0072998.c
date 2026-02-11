extract_file_finish_cb(
	gpointer user_data G_GNUC_UNUSED,
	uint16_t filenum G_GNUC_UNUSED,
	gpointer *file_data,
	gboolean truncated)
{
    if (truncated)
	g_fprintf(stderr, _("Data for '%s' may have been truncated\n"),
		(char *)*file_data);

    g_free(*file_data);

    return TRUE;
}
