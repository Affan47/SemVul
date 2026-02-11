undo_check_size(UndoMain *undostruct)
{
	UndoInfo *last_undo;
	guint length;

	if (prefs_common.undolevels < 1) return;


	length = g_list_length(undostruct->undo);
	if (length >= prefs_common.undolevels && prefs_common.undolevels > 0) {
		last_undo = (UndoInfo *)g_list_last(undostruct->undo)->data;
		undostruct->undo = g_list_remove(undostruct->undo, last_undo);
		undo_object_free(last_undo);
	}
}
