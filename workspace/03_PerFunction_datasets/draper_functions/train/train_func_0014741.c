get_strings_for_environment_variables (NemoView *view, GList *selected_files,
				       char **file_paths, char **uris, char **uri)
{
	char *directory_uri;


	directory_uri = nemo_directory_get_uri (view->details->model);
	if (g_str_has_prefix (directory_uri, "file:") ||
	    eel_uri_is_desktop (directory_uri) ||
	    eel_uri_is_trash (directory_uri)) {
		*file_paths = get_file_paths_as_newline_delimited_string (selected_files);
	} else {
		*file_paths = g_strdup ("");
	}
	g_free (directory_uri);

	*uris = get_file_uris_as_newline_delimited_string (selected_files);

	*uri = nemo_directory_get_uri (view->details->model);
	if (eel_uri_is_desktop (*uri)) {
		g_free (*uri);
		*uri = nemo_get_desktop_directory_uri ();
	}
}
