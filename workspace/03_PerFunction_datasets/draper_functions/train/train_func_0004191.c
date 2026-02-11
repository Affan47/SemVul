real_update_paste_menu (NemoView *view,
			GList *selection,
			gint selection_count)
{
	gboolean can_paste_files_into;
	gboolean selection_is_read_only;
	gboolean is_read_only;
	GtkAction *action;

	selection_is_read_only = selection_count == 1 &&
		(!nemo_file_can_write (NEMO_FILE (selection->data)) &&
		 !nemo_file_has_activation_uri (NEMO_FILE (selection->data)));

	is_read_only = nemo_view_is_read_only (view);

	can_paste_files_into = (selection_count == 1 &&
	                        can_paste_into_file (NEMO_FILE (selection->data)));

	action = gtk_action_group_get_action (view->details->dir_action_group,
					      NEMO_ACTION_PASTE);
	gtk_action_set_sensitive (action, !is_read_only);

	action = gtk_action_group_get_action (view->details->dir_action_group,
					      NEMO_ACTION_PASTE_FILES_INTO);
	gtk_action_set_visible (action, can_paste_files_into);
	gtk_action_set_sensitive (action, !selection_is_read_only);


	g_object_ref (view);
	gtk_clipboard_request_targets (nemo_clipboard_get (GTK_WIDGET (view)),
				       clipboard_targets_received,
				       view);
}
