insert_destination_at_position (ENameSelectorEntry *name_selector_entry,
                                gint pos)
{
	EDestination *destination;
	const gchar  *text;
	gint          index;

	text = gtk_entry_get_text (GTK_ENTRY (name_selector_entry));
	index = get_index_at_position (text, pos);

	destination = build_destination_at_position (text, pos);
	g_assert (destination);

	g_signal_handlers_block_by_func (
		name_selector_entry->priv->destination_store,
		destination_row_inserted, name_selector_entry);
	e_destination_store_insert_destination (
		name_selector_entry->priv->destination_store,
						index, destination);
	g_signal_handlers_unblock_by_func (
		name_selector_entry->priv->destination_store,
		destination_row_inserted, name_selector_entry);
	g_object_unref (destination);
}
