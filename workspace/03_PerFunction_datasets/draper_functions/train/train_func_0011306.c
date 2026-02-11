glade_signal_editor_handler_editing_started_default (GladeSignalEditor *editor,
                                                     gchar *signal_name,
                                                     GtkTreeIter *iter,
                                                     GtkCellEditable *editable)
{
	GladeSignalEditorPrivate *priv = editor->priv;
	GtkEntry *entry;
	GtkEntryCompletion *completion;
	GtkTreeModel *completion_store = priv->handler_store;

	g_return_val_if_fail (GTK_IS_BIN (editable), FALSE);
	g_return_val_if_fail (GTK_IS_LIST_STORE (completion_store), FALSE);

	entry = GTK_ENTRY (gtk_bin_get_child (GTK_BIN (editable)));

	glade_signal_editor_editing_started (entry, priv->is_void_handler);

	glade_signal_editor_handler_store_update (editor, signal_name,
						  GTK_LIST_STORE (completion_store));

	completion = gtk_entry_completion_new ();
	gtk_entry_completion_set_text_column (completion, 0);
	gtk_entry_completion_set_inline_completion (completion, TRUE);
	gtk_entry_completion_set_popup_completion (completion, FALSE);
	gtk_entry_completion_set_model (completion, completion_store);
	gtk_entry_set_completion (entry, completion);

	return FALSE;
}
