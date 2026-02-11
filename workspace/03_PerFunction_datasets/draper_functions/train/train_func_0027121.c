disable_spell_checking (AlmanahMainWindow *self)
{
	GtkSpellChecker *gtkspell;
	GtkTextTagTable *table;
	GtkTextTag *tag;

	gtkspell = gtk_spell_checker_get_from_text_view (self->priv->entry_view);
	if (gtkspell != NULL)
		gtk_spell_checker_detach (gtkspell);


	table = gtk_text_buffer_get_tag_table (self->priv->entry_buffer);
	tag = gtk_text_tag_table_lookup (table, "gtkspell-misspelled");
	if (tag != NULL)
		gtk_text_tag_table_remove (table, tag);


	gtk_text_buffer_create_tag (self->priv->entry_buffer, "gtkspell-misspelled", NULL);
}
