enable_spell_checking (AlmanahMainWindow *self, GError **error)
{
	AlmanahApplication *application;
	GSettings *settings;
	GtkSpellChecker *gtkspell;
	gchar *spelling_language;
	GtkTextTagTable *table;
	GtkTextTag *tag;


	if (gtk_spell_checker_get_from_text_view (self->priv->entry_view) != NULL)
		return TRUE;


	table = gtk_text_buffer_get_tag_table (self->priv->entry_buffer);
	tag = gtk_text_tag_table_lookup (table, "gtkspell-misspelled");
	if (tag != NULL)
		gtk_text_tag_table_remove (table, tag);


	application = ALMANAH_APPLICATION (gtk_window_get_application (GTK_WINDOW (self)));
	settings = almanah_application_dup_settings (application);
	spelling_language = g_settings_get_string (settings, "spelling-language");
	g_object_unref (settings);


	if (spelling_language != NULL && spelling_language[0] == '\0') {
		g_free (spelling_language);
		spelling_language = NULL;
	}

	gtkspell = gtk_spell_checker_new ();
	gtk_spell_checker_set_language (gtkspell, spelling_language, error);
	gtk_spell_checker_attach (gtkspell, self->priv->entry_view);
	g_free (spelling_language);

	if (gtkspell == NULL)
		return FALSE;
	return TRUE;
}
