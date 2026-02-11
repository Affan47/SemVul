git_repository_is_empty(git_repository *repo)
{
	git_reference *head, *branch;
	int error;

	error = git_reference_lookup(&head, repo, "HEAD");
	if (error < GIT_SUCCESS)
		return git__throw(error, "Corrupted repository. HEAD does not exist");

	if (git_reference_type(head) != GIT_REF_SYMBOLIC)
		return 0;

	if (strcmp(git_reference_target(head), "refs/heads/master") != 0)
		return 0;

	error = git_reference_resolve(&branch, head);
	return error == GIT_ENOTFOUND ? 1 : error;
}
