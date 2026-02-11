on_commit_diff_button_clicked (GtkAction *action, Git *plugin)
{
	GitRevision *revision;
	gchar *sha;
	gchar *short_sha;
	gchar *editor_name;
	IAnjutaDocumentManager *document_manager;
	IAnjutaEditor *editor;
	GitDiffTreeCommand *diff_command;

	revision = git_log_pane_get_selected_revision (GIT_LOG_PANE (plugin->log_pane));

	if (revision)
	{
		sha = git_revision_get_sha (revision);
		short_sha = git_revision_get_short_sha (revision);

		editor_name = g_strdup_printf (_("Commit %s.diff"), short_sha);

		document_manager = anjuta_shell_get_interface (ANJUTA_PLUGIN (plugin)->shell,
													   IAnjutaDocumentManager,
													   NULL);
		editor = ianjuta_document_manager_add_buffer (document_manager,
													  editor_name,
													  "", NULL);

		diff_command = git_diff_tree_command_new (plugin->project_root_directory,
												  sha);

		g_signal_connect (G_OBJECT (diff_command), "data-arrived",
						  G_CALLBACK (git_pane_send_raw_output_to_editor),
						  editor);

		g_signal_connect (G_OBJECT (diff_command), "command-finished",
						  G_CALLBACK (git_pane_report_errors),
						  plugin);

		g_signal_connect (G_OBJECT (diff_command), "command-finished",
						  G_CALLBACK (g_object_unref),
						  NULL);


		anjuta_command_start (ANJUTA_COMMAND (diff_command));

		g_object_unref (revision);
		g_free (sha);
		g_free (short_sha);
		g_free (editor_name);
	}
	else
		anjuta_util_dialog_error (NULL, _("No revision selected"));
}
