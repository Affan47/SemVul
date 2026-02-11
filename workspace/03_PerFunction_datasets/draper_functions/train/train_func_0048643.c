cb_dialog_so_size_apply_clicked (G_GNUC_UNUSED GtkWidget *button,
				   SOSizeState *state)
{
	char const *name;
	GOUndo *undo = NULL, *redo = NULL;
	char const *undo_name = NULL;
	int cnt = 0;

	if (state->so_size_needs_restore || state->so_pos_needs_restore) {
		char const *label = state->so_pos_needs_restore ?
			_("Move Object") : _("Resize Object");
		sheet_object_set_anchor	(state->so, state->old_anchor);
		if (!cmd_objects_move (WORKBOOK_CONTROL (state->wbcg),
				       g_slist_prepend (NULL, state->so),
				       g_slist_prepend
				       (NULL, sheet_object_anchor_dup
					(state->active_anchor)),
				       FALSE, label))
			dialog_so_size_load (state);
	}

	name = gtk_entry_get_text (state->nameentry);
	if (name == NULL)
		name = "";
	if (strcmp (name, state->old_name) != 0) {
		char *old_name, *new_name;

		g_object_get (G_OBJECT (state->so), "name", &old_name, NULL);
		undo = go_undo_combine (undo, set_params (state->so, old_name));

		new_name = (*name == '\0') ? NULL : g_strdup (name);
		redo = go_undo_combine (redo, set_params (state->so, new_name));

		undo_name = _("Set Object Name");
		cnt++;
	}
	if (state->so_print_check_changed) {
		gboolean val = ((state->so->flags & SHEET_OBJECT_PRINT) != 0);
		undo = go_undo_combine (undo, set_print_flag
					(state->so,  val));
		redo = go_undo_combine (redo, set_print_flag
					(state->so, !val));
		undo_name =  _("Set Object Print Property");
		cnt++;
	}

	if (cnt > 0) {
		if (cnt > 1)
			undo_name =  _("Set Object Properties");
		state->so_name_changed = state->so_print_check_changed =
			cmd_generic (WORKBOOK_CONTROL (state->wbcg),
				     undo_name, undo, redo);
	}
	dialog_so_size_button_sensitivity (state);

	return;
}
