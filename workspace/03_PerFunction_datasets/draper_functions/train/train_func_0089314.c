lookup_head_remote_key(git_buf *remote_name, git_repository *repo)
{
	int error;
	git_reference *head = NULL;
	git_buf upstream_name = GIT_BUF_INIT;


	if ((error = git_repository_head(&head, repo)) < 0)
		return error;


	if (!(error = git_branch_upstream_name(
			&upstream_name, repo, git_reference_name(head))))
	{

		error = git_branch_remote_name(remote_name, repo, upstream_name.ptr);

		git_buf_free(&upstream_name);
	}

	git_reference_free(head);

	return error;
}
