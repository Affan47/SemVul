set_index(git_repository *repo, git_index *index)
{
	if (index) {
		GIT_REFCOUNT_OWN(index, repo);
		GIT_REFCOUNT_INC(index);
	}

	if ((index = git__swap(repo->_index, index)) != NULL) {
		GIT_REFCOUNT_OWN(index, NULL);
		git_index_free(index);
	}
}
