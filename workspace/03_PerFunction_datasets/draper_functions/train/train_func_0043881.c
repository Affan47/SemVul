git_refs_handle_output (GiggleJob   *job,
			const gchar *output_str,
			gsize        output_len)
{
	GiggleGitRefsPriv  *priv;
	gchar             **lines;
	gint                n_line = 0;

	priv = GET_PRIV (job);
	lines = g_strsplit (output_str, "\n", -1);

	while (lines[n_line] && *lines[n_line]) {
		git_refs_add_ref (job, lines[n_line]);
		n_line++;
	}

	priv->branches = g_list_reverse (priv->branches);
	priv->tags = g_list_reverse (priv->tags);
	g_strfreev (lines);
}
