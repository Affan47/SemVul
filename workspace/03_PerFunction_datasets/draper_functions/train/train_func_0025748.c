gitg_repository_get_refs_for_hash (GitgRepository *repository,
                                   gchar const    *hash)
{
	g_return_val_if_fail (GITG_IS_REPOSITORY (repository), NULL);
	return g_slist_copy ( (GSList *)g_hash_table_lookup (repository->priv->refs, hash));
}
