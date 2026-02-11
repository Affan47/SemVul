nemo_file_undo_info_strings_func (NemoFileUndoInfo *self,
				      gchar **undo_label,
				      gchar **undo_description,
				      gchar **redo_label,
				      gchar **redo_description)
{
	if (undo_label != NULL) {
		*undo_label = g_strdup (_("Undo"));
	}
	if (undo_description != NULL) {
		*undo_description = g_strdup (_("Undo last action"));
	}

	if (redo_label != NULL) {
		*redo_label = g_strdup (_("Redo"));
	}
	if (redo_description != NULL) {
		*redo_description = g_strdup (_("Redo last undone action"));
	}
}
