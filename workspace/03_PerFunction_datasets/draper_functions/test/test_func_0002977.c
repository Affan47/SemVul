update_fm_module_ui (BasicAutotoolsPlugin *bb_plugin)
{
	AnjutaUI *ui;
	GtkAction *action;
	gboolean has_file = FALSE;
	gboolean has_makefile= FALSE;
	gboolean has_project = TRUE;
	gboolean has_object = FALSE;
	gboolean is_directory = FALSE;

	ui = anjuta_shell_get_ui (ANJUTA_PLUGIN (bb_plugin)->shell, NULL);

	has_file = bb_plugin->fm_current_file != NULL;
	if (has_file)
	{
		GFile *mod;

		mod = build_module_from_file (bb_plugin, bb_plugin->fm_current_file, NULL);
		if (mod != NULL)
		{
			has_makefile = directory_has_makefile (mod) || directory_has_makefile_am (bb_plugin, mod);
			g_object_unref (mod);
		}

		is_directory = g_file_query_file_type (bb_plugin->fm_current_file, 0, NULL) == G_FILE_TYPE_DIRECTORY;
		if (!is_directory)
		{
			mod = build_object_from_file (bb_plugin, bb_plugin->fm_current_file);
			if (mod != NULL)
			{
				has_object = TRUE;
				g_object_unref (mod);
			}
		}
	}
	has_project = bb_plugin->project_root_dir != NULL;

	action = anjuta_ui_get_action (ui, "ActionGroupPopupBuild",
									   "ActionPopupBuild");
	g_object_set (G_OBJECT (action), "visible", has_file && (has_makefile || (!is_directory && !has_project)), NULL);

	action = anjuta_ui_get_action (ui, "ActionGroupPopupBuild",
								   "ActionPopupBuildCompile");
	g_object_set (G_OBJECT (action), "sensitive", has_object, "visible", !is_directory, NULL);

	action = anjuta_ui_get_action (ui, "ActionGroupPopupBuild",
								   "ActionPopupBuildBuild");
	g_object_set (G_OBJECT (action), "sensitive", has_file && (has_makefile || (!is_directory && !has_project)), NULL);

	action = anjuta_ui_get_action (ui, "ActionGroupPopupBuild",
								   "ActionPopupBuildInstall");
	g_object_set (G_OBJECT (action), "sensitive", has_makefile, "visible", has_project, NULL);

	action = anjuta_ui_get_action (ui, "ActionGroupPopupBuild",
								   "ActionPopupBuildClean");
	g_object_set (G_OBJECT (action), "sensitive", has_makefile, "visible", has_project, NULL);
}
