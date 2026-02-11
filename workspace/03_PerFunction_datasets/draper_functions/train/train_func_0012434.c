python_assist_create_word_completion_cache (PythonAssist *assist, IAnjutaIterable* cursor)
{
	IAnjutaEditor *editor = IANJUTA_EDITOR (assist->priv->iassist);
	const gchar *cur_filename;
	gint offset = ianjuta_iterable_get_position (cursor, NULL);
	const gchar *project = assist->priv->project_root;
	gchar *interpreter_path;
	gchar *ropecommand;
	GString *builder_file_paths = g_string_new("");
	GList *project_files_list, *node;
	gchar *python_content_type;

	gchar *source = ianjuta_editor_get_text_all (editor, NULL);
	gchar *tmp_file;

	cur_filename = assist->priv->editor_filename;
	if (!project)
		project = g_get_tmp_dir ();


	interpreter_path = g_settings_get_string (assist->priv->settings,
	                                          PREF_INTERPRETER_PATH);

	tmp_file = create_tmp_file (source);
	g_free (source);

	if (!tmp_file)
		return FALSE;


	IAnjutaProjectManager *manager = anjuta_shell_get_interface (ANJUTA_PLUGIN (assist->priv->plugin)->shell,
								     IAnjutaProjectManager,
								     NULL);
	project_files_list = ianjuta_project_manager_get_elements (IANJUTA_PROJECT_MANAGER (manager),
								   ANJUTA_PROJECT_SOURCE,
								   NULL);
	python_content_type = g_content_type_from_mime_type ("text/x-python");
	for (node = project_files_list; node != NULL; node = g_list_next (node))
	{
		gchar *filename, *content_type;

		filename = g_file_get_basename (node->data);
		content_type = g_content_type_guess (filename, NULL, 0, NULL);

		if (g_content_type_equals (content_type, python_content_type))
		{
			gchar *file_path = g_file_get_path (node->data);
			builder_file_paths = g_string_append (builder_file_paths, FILE_LIST_DELIMITER);
			builder_file_paths = g_string_append (builder_file_paths, file_path);
			g_free (file_path);
		}

		g_free (filename);
		g_free (content_type);
		g_object_unref (node->data);
	}
	g_list_free (project_files_list);
	g_free (python_content_type);

	ropecommand = g_strdup_printf("%s %s -o autocomplete -p \"%s\" -r \"%s\" -s \"%s\" -f %d -b \"%s\"",
	                              interpreter_path, AUTOCOMPLETE_SCRIPT, project,
	                              cur_filename, tmp_file, offset, builder_file_paths->str);
	g_string_free (builder_file_paths, TRUE);
	g_free (tmp_file);

	DEBUG_PRINT("%s", ropecommand);


	assist->priv->launcher = anjuta_launcher_new ();
	g_signal_connect (assist->priv->launcher, "child-exited",
	                  G_CALLBACK(on_autocomplete_finished), assist);
	anjuta_launcher_execute (assist->priv->launcher, ropecommand,
	                         on_autocomplete_output,
	                         assist);
	g_free (ropecommand);

	assist->priv->cache_position = offset;

	return TRUE;
}
