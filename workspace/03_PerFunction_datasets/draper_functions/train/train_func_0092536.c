git_revisions_get_revision (GiggleGitRevisionsPriv *priv,
			    const gchar            *str,
			    GHashTable             *revisions_hash)
{
	GiggleRevision *revision, *parent;
	gchar **lines, **ids;
	gint i = 1;

	lines = g_strsplit (str, "\n", -1);
	ids = g_strsplit (lines[0], " ", -1);

	if (!(revision = g_hash_table_lookup (revisions_hash, ids[0]))) {

		revision = giggle_revision_new (ids[0]);
		g_hash_table_insert (revisions_hash, g_strdup (ids[0]), revision);
	}


	while (ids[i] != NULL) {
		if (!(parent = g_hash_table_lookup (revisions_hash, ids[i]))) {
			parent = giggle_revision_new (ids[i]);
			g_hash_table_insert (revisions_hash, g_strdup (ids[i]), parent);
		}

		giggle_revision_add_parent (revision, parent);
		i++;
	}

	git_revisions_parse_revision_info (priv, revision, lines);

	g_strfreev (ids);
	g_strfreev (lines);

	return g_object_ref (revision);
}
