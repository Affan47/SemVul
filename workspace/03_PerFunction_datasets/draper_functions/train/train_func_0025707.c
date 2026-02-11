on_commit_file_removed (GitgCommit      *commit,
                        GitgChangedFile *file,
                        GitgCommitView  *view)
{
	GtkTreeIter iter;

	if (find_file_in_store (view->priv->store_staged, file, &iter))
	{
		gtk_list_store_remove (view->priv->store_staged, &iter);
	}

	if (find_file_in_store (view->priv->store_unstaged, file, &iter))
	{
		gtk_list_store_remove (view->priv->store_unstaged, &iter);
	}
}
