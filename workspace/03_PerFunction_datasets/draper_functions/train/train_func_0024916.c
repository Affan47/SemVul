text_from_size_abrev(gint64 size)
{
	if (size < (gint64)1024)
		{
		return g_strdup_printf(_("%d bytes"), (gint)size);
		}
	if (size < (gint64)1048576)
		{
		return g_strdup_printf(_("%.1f K"), (gdouble)size / 1024.0);
		}
	if (size < (gint64)1073741824)
		{
		return g_strdup_printf(_("%.1f MB"), (gdouble)size / 1048576.0);
		}


	size /= 1048576;
	return g_strdup_printf(_("%.1f GB"), (gdouble)size / 1024.0);
}
