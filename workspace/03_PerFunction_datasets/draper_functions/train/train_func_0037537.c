on_ok_action_activated (GtkAction *action, GitDeleteBranchesPane *self)
{
	Git *plugin;
	GtkToggleButton *require_merged_check;
	GList *selected_local_branches;
	GList *selected_remote_branches;
	GitBranchDeleteCommand *local_delete_command;
	GitBranchDeleteCommand *remote_delete_command;
	AnjutaCommandQueue *queue;

	plugin = ANJUTA_PLUGIN_GIT (anjuta_dock_pane_get_plugin (ANJUTA_DOCK_PANE (self)));
	require_merged_check = GTK_TOGGLE_BUTTON (gtk_builder_get_object (self->priv->builder,
	                                                                  "require_merged_check"));
	selected_local_branches = git_branches_pane_get_selected_local_branches (GIT_BRANCHES_PANE (plugin->branches_pane));
	selected_remote_branches = git_branches_pane_get_selected_remote_branches (GIT_BRANCHES_PANE (plugin->branches_pane));


	if (git_branches_pane_count_selected_items (GIT_BRANCHES_PANE (plugin->branches_pane)) > 0)
	{
		queue = anjuta_command_queue_new (ANJUTA_COMMAND_QUEUE_EXECUTE_MANUAL);

		if (selected_local_branches)
		{
			local_delete_command = git_branch_delete_command_new (plugin->project_root_directory,
			                                                      selected_local_branches,
			                                                      FALSE,
			                                                      gtk_toggle_button_get_active (require_merged_check));

			anjuta_util_glist_strings_free (selected_local_branches);

			g_signal_connect (G_OBJECT (local_delete_command),
			                  "command-finished",
			                  G_CALLBACK (git_pane_report_errors),
			                  plugin);


			g_signal_connect (G_OBJECT (local_delete_command),
			                  "command-finished",
			                  G_CALLBACK (g_object_unref),
			                  NULL);

			anjuta_command_queue_push (queue,
			                           ANJUTA_COMMAND (local_delete_command));
		}

		if (selected_remote_branches)
		{
			remote_delete_command = git_branch_delete_command_new (plugin->project_root_directory,
			                                                       selected_remote_branches,
			                                                       TRUE,
			                                                       gtk_toggle_button_get_active (require_merged_check));

			anjuta_util_glist_strings_free (selected_remote_branches);

			g_signal_connect (G_OBJECT (remote_delete_command),
			                  "command-finished",
			                  G_CALLBACK (git_pane_report_errors),
			                  plugin);


			g_signal_connect (G_OBJECT (remote_delete_command), "command-finished",
			                  G_CALLBACK (g_object_unref),
			                  NULL);

			anjuta_command_queue_push (queue,
			                           ANJUTA_COMMAND (remote_delete_command));
		}


		g_signal_connect (G_OBJECT (queue), "finished",
		                  G_CALLBACK (g_object_unref),
		                  NULL);

		anjuta_command_queue_start (queue);
	}


	git_pane_remove_from_dock (GIT_PANE (self));

}
