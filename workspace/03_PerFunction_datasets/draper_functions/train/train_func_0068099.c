giggle_remote_new_from_file (gchar const *filename)
{
	GiggleRemote *remote;
	gchar        *content;

	content = g_path_get_basename (filename);
	remote = giggle_remote_new (content);
	g_free (content);
	content = NULL;

	if(g_file_get_contents (filename, &content, NULL, NULL)) {
		gchar**lines;
		gchar**step;
		lines = g_strsplit (content, "\n", -1);
		for (step = lines; step && *step; step++) {
			GiggleRemoteBranch* branch = NULL;
			if(!**step) {

				continue;
			} else if(g_str_has_prefix(*step, "URL: ")) {
				giggle_remote_set_url (remote, *step + strlen ("URL: "));
			} else if(g_str_has_prefix(*step, "Push: ")) {
				branch = giggle_remote_branch_new (GIGGLE_REMOTE_DIRECTION_PUSH,
								   *step + strlen ("Push: "));
			} else if(g_str_has_prefix(*step, "Pull: ")) {
				branch = giggle_remote_branch_new (GIGGLE_REMOTE_DIRECTION_PULL,
								   *step + strlen ("Pull: "));
			} else {
				gchar* escaped = g_strescape (*step, NULL);
				g_warning ("Read unexpected line at %s:%td\n\"%s\"",
					   filename, step - lines, escaped);
				g_free (escaped);
			}

			if(GIGGLE_IS_REMOTE_BRANCH (branch)) {
				giggle_remote_add_branch (remote, branch);
				g_object_unref (branch);
				branch = NULL;
			}
		}
		g_strfreev (lines);
	}
	g_free (content);

	return remote;
}
