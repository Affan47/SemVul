push_three_states(void)
{
	git_oid oid;
	git_index *index;

	cl_git_mkfile("stash/zero.txt", "content\n");
	cl_git_pass(git_repository_index(&index, repo));
	cl_git_pass(git_index_add_from_workdir(index, "zero.txt"));
	commit_staged_files(&oid, index, signature);

	cl_git_mkfile("stash/one.txt", "content\n");
	cl_git_pass(git_stash_save(&oid, repo, signature, "First", GIT_STASH_INCLUDE_UNTRACKED));

	cl_git_mkfile("stash/two.txt", "content\n");
	cl_git_pass(git_stash_save(&oid, repo, signature, "Second", GIT_STASH_INCLUDE_UNTRACKED));

	cl_git_mkfile("stash/three.txt", "content\n");
	cl_git_pass(git_stash_save(&oid, repo, signature, "Third", GIT_STASH_INCLUDE_UNTRACKED));

	git_index_free(index);
}
