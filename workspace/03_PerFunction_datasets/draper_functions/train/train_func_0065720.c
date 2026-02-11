editable_register_edit_undo (GtkEditable *editable)
{
	EditableUndoData *undo_data;
	EditableUndoObjectData *undo_info;
	gpointer data;

	if (!GTK_IS_EDITABLE (editable) ) {
		return;
	}


	data = g_object_get_data (G_OBJECT (editable), "undo_registered");
	if (data == NULL) {
		g_warning ("Undo data is NULL");
		return;
	}

	undo_info = (EditableUndoObjectData *)data;
	if (undo_info->undo_registered) {
		return;
	}

	undo_data = g_new0 (EditableUndoData, 1);
	undo_data->undo_text = gtk_editable_get_chars (editable, 0, -1);
	undo_data->position = gtk_editable_get_position (editable);
	gtk_editable_get_selection_bounds (editable,
					   &undo_data->selection_start,
					   &undo_data->selection_end);

	nemo_undo_register
		(G_OBJECT (editable),
		 restore_editable_from_undo_snapshot_callback,
		 undo_data,
		 (GDestroyNotify) free_editable_undo_data,
		 _("Edit"),
		 _("Undo Edit"),
		 _("Undo the edit"),
		 _("Redo Edit"),
		 _("Redo the edit"));

	undo_info->undo_registered = TRUE;
}
