git_ref_command_insert_ref (GitRefCommand *self, const gchar *sha, GitRef *ref)
{
	GList *ref_list;
	gchar *name;
	gchar *old_sha;

	name = git_ref_get_name (ref);

	ref_list = g_hash_table_lookup (self->priv->refs, sha);

	ref_list = g_list_append (ref_list, ref);

	if (g_hash_table_lookup_extended (self->priv->refs, sha,
									  (gpointer) &old_sha, NULL))
	{

		g_hash_table_steal (self->priv->refs, sha);

		g_free (old_sha);
	}

	g_hash_table_insert (self->priv->refs, g_strdup (sha), ref_list);

	g_free (name);
}
