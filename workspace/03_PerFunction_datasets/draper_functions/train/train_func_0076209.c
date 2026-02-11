spell_entry_populate_popup (ESpellEntry *entry,
                            GtkMenu *menu,
                            gpointer data)
{
	gint start, end;
	gchar *word;

	if (entry->priv->checkers == NULL)
		return;

	get_word_extents_from_position (
		entry, &start, &end, entry->priv->mark_character);
	if (start == end)
		return;

	if (!word_misspelled (entry, start, end))
		return;

	word = gtk_editable_get_chars (GTK_EDITABLE (entry), start, end);
	g_return_if_fail (word != NULL);

	spell_entry_add_suggestions_menu (entry, menu, word);

	g_free (word);
}
