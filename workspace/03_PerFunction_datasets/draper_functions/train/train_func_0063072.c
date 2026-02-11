labels_set_ram(uint32_t ram)
{
	gchar *str = NULL;

	if (ram < 1024)
		str = g_strdup_printf(_("%d bytes"), ram);
	if (ram >= 1024 && ram < 1048576)
		str = g_strdup_printf(_("%.1f KB"), (float)(ram / 1024));
	if (ram >= 1048576)
		str = g_strdup_printf(_("%.1f MB"), (float)(ram / 1048576));

	gtk_label_set_text(GTK_LABEL(gfm_widget.ram), str);
	g_free(str);
}
