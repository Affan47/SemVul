stage_content(char *content[])
{
	git_reference *head;
	git_object *head_object;
	git_buf path = GIT_BUF_INIT;
	char *filename, *text;
	size_t i;

	cl_git_pass(git_repository_head(&head, repo));
	cl_git_pass(git_reference_peel(&head_object, head, GIT_OBJ_COMMIT));
	cl_git_pass(git_reset(repo, head_object, GIT_RESET_HARD, NULL, NULL, NULL));

	for (i = 0, filename = content[i], text = content[++i];
		filename && text;
		filename = content[++i], text = content[++i]) {

		git_buf_clear(&path);

		cl_git_pass(git_buf_printf(&path, "%s/%s", TEST_REPO_PATH, filename));

		cl_git_mkfile(path.ptr, text);
		cl_git_pass(git_index_add_bypath(repo_index, filename));
	}

	git_object_free(head_object);
	git_reference_free(head);
	git_buf_free(&path);
}
