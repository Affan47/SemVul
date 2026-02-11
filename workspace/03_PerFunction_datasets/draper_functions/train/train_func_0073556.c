git_note_iterator_new(
	git_note_iterator **it,
	git_repository *repo,
	const char *notes_ref)
{
	int error;
	git_commit *commit = NULL;
	git_tree *tree = NULL;

	error = retrieve_note_tree_and_commit(&tree, &commit, repo, &notes_ref);
	if (error < 0)
		goto cleanup;

	if ((error = git_iterator_for_tree(it, tree, 0, NULL, NULL)) < 0)
		git_iterator_free(*it);

cleanup:
	git_tree_free(tree);
	git_commit_free(commit);

	return error;
}
