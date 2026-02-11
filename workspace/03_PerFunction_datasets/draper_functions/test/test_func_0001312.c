brasero_rename_delete_string (BraseroRename *self,
			      const gchar *name)
{
	BraseroRenamePrivate *priv;
	const gchar *text;
	gchar *occurrence;

	priv = BRASERO_RENAME_PRIVATE (self);

	text = gtk_entry_get_text (GTK_ENTRY (priv->delete_entry));
	occurrence = g_strstr_len (name, -1, text);

	if (!occurrence)
		return NULL;

	return g_strdup_printf ("%.*s%s", (int) (occurrence - name), name, occurrence + strlen (text));
}
