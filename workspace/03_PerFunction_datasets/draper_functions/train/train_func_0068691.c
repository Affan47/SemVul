loader_update_commits (GitgRepository  *self,
                       gchar          **buffer)
{
	gchar *line;

	while ( (line = *buffer++) != NULL)
	{

		gchar **components = g_strsplit (line, "\01", 0);
		guint len = g_strv_length (components);

		if (len < 9)
		{
			g_strfreev (components);
			continue;
		}


		gint64 author_date = g_ascii_strtoll (components[3], NULL, 0);
		gint64 committer_date = g_ascii_strtoll (components[6], NULL, 0);

		GitgRevision *rv = gitg_revision_new (components[0],
		                                      components[1],
		                                      components[2],
		                                      author_date,
		                                      components[4],
		                                      components[5],
		                                      committer_date,
		                                      components[7],
		                                      components[8]);

		if (len > 9 && strlen (components[9]) == 1 && strchr ("<>-^", *components[9]) != NULL)
		{
			gitg_revision_set_sign (rv, *components[9]);
		}

		append_revision (self, rv);
		g_strfreev (components);
	}
}
