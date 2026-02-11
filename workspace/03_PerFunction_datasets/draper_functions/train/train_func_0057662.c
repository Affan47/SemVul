on_resolve_conflicts_button_clicked (GtkAction *action, Git *plugin)
{
	GList *paths;
	GitAddCommand *add_command;

	paths = git_status_pane_get_all_checked_items (GIT_STATUS_PANE (plugin->status_pane),
	                                               ANJUTA_VCS_STATUS_CONFLICTED);

	if (paths)
	{
		add_command = git_add_command_new_list (plugin->project_root_directory,
		                                        paths, FALSE);

		anjuta_util_glist_strings_free (paths);

		g_signal_connect (G_OBJECT (add_command), "command-finished",
		                  G_CALLBACK (git_pane_report_errors),
		                  plugin);


		g_signal_connect (G_OBJECT (add_command), "command-finished",
		                  G_CALLBACK (g_object_unref),
		                  NULL);

		anjuta_command_start (ANJUTA_COMMAND (add_command));
	}
	else
		anjuta_util_dialog_error (NULL, _("No conflicted files selected."));
}
