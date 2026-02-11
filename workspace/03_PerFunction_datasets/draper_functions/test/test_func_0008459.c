action_open_scripts_folder_callback (GtkAction *action,
				     gpointer callback_data)
{
	NemoView *view;
	static GFile *location = NULL;

	if (location == NULL) {
		location = g_file_new_for_uri (scripts_directory_uri);
	}

	view = NEMO_VIEW (callback_data);
	nemo_window_slot_go_to (view->details->slot, location, FALSE);

	eel_show_info_dialog_with_details
		(_("All executable files in this folder will appear in the "
		   "Scripts menu."),
		 _("Choosing a script from the menu will run "
		   "that script with any selected items as input."),
		 _("All executable files in this folder will appear in the "
		   "Scripts menu. Choosing a script from the menu will run "
		   "that script.\n\n"
		   "When executed from a local folder, scripts will be passed "
		   "the selected file names. When executed from a remote folder "
		   "(e.g. a folder showing web or ftp content), scripts will "
		   "be passed no parameters.\n\n"
		   "In all cases, the following environment variables will be "
		   "set by Nemo, which the scripts may use:\n\n"
		   "NEMO_SCRIPT_SELECTED_FILE_PATHS: newline-delimited paths for selected files (only if local)\n\n"
		   "NEMO_SCRIPT_SELECTED_URIS: newline-delimited URIs for selected files\n\n"
		   "NEMO_SCRIPT_CURRENT_URI: URI for current location\n\n"
		   "NEMO_SCRIPT_WINDOW_GEOMETRY: position and size of current window\n\n"
		   "NEMO_SCRIPT_NEXT_PANE_SELECTED_FILE_PATHS: newline-delimited paths for selected files in the inactive pane of a split-view window (only if local)\n\n"
		   "NEMO_SCRIPT_NEXT_PANE_SELECTED_URIS: newline-delimited URIs for selected files in the inactive pane of a split-view window\n\n"
		   "NEMO_SCRIPT_NEXT_PANE_CURRENT_URI: URI for current location in the inactive pane of a split-view window"),
		 nemo_view_get_containing_window (view));
}
