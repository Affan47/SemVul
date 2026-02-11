text_editor_hilite_one (TextEditor * te, AnEditorID editor_id)
{
	const gchar *name = NULL;
	gchar *basename = NULL;


	if (!te->force_pref ||
		!g_settings_get_boolean (te->settings,
									DISABLE_SYNTAX_HILIGHTING))
	{
		if (te->force_hilite)
		{
			name = te->force_hilite;
		}
		else if (te->uri)
		{
			basename = g_path_get_basename (te->uri);
			name = basename;
		}
		else if (te->filename)
		{
			name = te->filename;
		}
	}

	if (name == NULL)
	{

		aneditor_command (editor_id, ANE_SETHILITE, (glong) "plain.txt", (glong) 0);
	}
	else
	{
		const gchar *typedef_hl[2];
		GValue sys_value = {0,};
		GValue prj_value = {0,};

		anjuta_shell_get_value (te->shell, TEXT_EDITOR_SYSTEM_TYPE_LIST, &sys_value, NULL);
		typedef_hl[0] = G_VALUE_HOLDS_STRING(&sys_value) ? g_value_get_string (&sys_value) : NULL;

		anjuta_shell_get_value (te->shell, TEXT_EDITOR_PROJECT_TYPE_LIST, &prj_value, NULL);
		typedef_hl[1] = G_VALUE_HOLDS_STRING(&prj_value) ? g_value_get_string (&prj_value) : NULL;

		aneditor_command (editor_id, ANE_SETHILITE, (glong) name, (glong) typedef_hl);
		if (G_IS_VALUE (&sys_value)) g_value_unset (&sys_value);
		if (G_IS_VALUE (&prj_value)) g_value_unset (&prj_value);
	}
	g_free (basename);
}
