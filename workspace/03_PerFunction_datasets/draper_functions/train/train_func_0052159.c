file_entry_changed (GtkEntry *entry, const char *key)
{
	GnomeFileEntry *file_entry;
	GConfClient *gconf;
	char *str;

	gconf = gconf_client_get_default ();

	file_entry = (GnomeFileEntry *) gtk_widget_get_ancestor ((GtkWidget *) entry, GNOME_TYPE_FILE_ENTRY);

	str = gnome_file_entry_get_full_path (file_entry, FALSE);
	gconf_client_set_string (gconf, key, str ? str : "", NULL);
	g_free (str);

	g_object_unref (gconf);
}
