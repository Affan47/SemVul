giggle_git_diff_tree_get_sha1 (GiggleGitDiffTree *job,
			       const char        *file)
{
	GiggleGitDiffTreePriv *priv;

	g_return_val_if_fail (GIGGLE_IS_GIT_DIFF_TREE (job), NULL);
	g_return_val_if_fail (NULL != file, NULL);

	priv = GET_PRIV (job);

	return g_hash_table_lookup (priv->sha_table1, file);
}
