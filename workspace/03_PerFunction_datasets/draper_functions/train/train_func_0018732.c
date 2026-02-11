go_undo_group_undo (GOUndo *u, gpointer data)
{
	GOUndoGroup *ug = (GOUndoGroup *)u;
	unsigned i;

	for (i = ug->undos->len; i-- > 0; ) {
		GOUndo *u_ = g_ptr_array_index (ug->undos, i);
		go_undo_undo_with_data (u_, data);
	}
}
