run_plugin_update_shell_value (RunProgramPlugin *plugin)
{
	gchar *dir_uri;
	gchar *target_uri;


	target_uri = plugin->recent_target == NULL ? NULL : g_file_get_uri ((GFile *)plugin->recent_target->data);
	dir_uri = plugin->recent_dirs == NULL ? NULL : g_file_get_uri ((GFile *)plugin->recent_dirs->data);
	anjuta_shell_add (ANJUTA_PLUGIN (plugin)->shell,
					 	RUN_PROGRAM_URI, G_TYPE_STRING, target_uri,
						RUN_PROGRAM_ARGS, G_TYPE_STRING, plugin->recent_args == NULL ? NULL : plugin->recent_args->data,
					    RUN_PROGRAM_DIR, G_TYPE_STRING, dir_uri,
					  	RUN_PROGRAM_ENV, G_TYPE_STRV, plugin->environment_vars == NULL ? NULL : plugin->environment_vars,
						RUN_PROGRAM_NEED_TERM, G_TYPE_BOOLEAN, plugin->run_in_terminal,
					  	NULL);
	g_free (dir_uri);
	g_free (target_uri);
}
