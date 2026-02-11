setup_stash(git_repository *repo, git_signature *signature)
{
	git_oid commit_oid;
	git_index *index;

	cl_git_pass(git_repository_index(&index, repo));

	cl_git_mkfile("stash/what", "hello\n");
	cl_git_mkfile("stash/how", "small\n");
	cl_git_mkfile("stash/who", "world\n");
	cl_git_mkfile("stash/when", "now\n");
	cl_git_mkfile("stash/just.ignore", "me\n");

	cl_git_mkfile("stash/.gitignore", "*.ignore\n");

	cl_git_pass(git_index_add_from_workdir(index, "what"));
	cl_git_pass(git_index_add_from_workdir(index, "how"));
	cl_git_pass(git_index_add_from_workdir(index, "who"));
	cl_git_pass(git_index_add_from_workdir(index, ".gitignore"));
	cl_git_pass(git_index_write(index));

	commit_staged_files(&commit_oid, index, signature);

	cl_git_rewritefile("stash/what", "goodbye\n");
	cl_git_rewritefile("stash/how", "not so small and\n");
	cl_git_rewritefile("stash/who", "funky world\n");

	cl_git_pass(git_index_add_from_workdir(index, "what"));
	cl_git_pass(git_index_add_from_workdir(index, "how"));
	cl_git_pass(git_index_write(index));

	cl_git_rewritefile("stash/what", "see you later\n");

	git_index_free(index);
}
