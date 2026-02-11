test_diff_format_email__invalid_no(void)
{
	git_oid oid;
	git_commit *commit = NULL;
	git_diff *diff = NULL;
	git_diff_format_email_options opts = GIT_DIFF_FORMAT_EMAIL_OPTIONS_INIT;
	git_buf buf = GIT_BUF_INIT;

	git_oid_fromstr(&oid, "9264b96c6d104d0e07ae33d3007b6a48246c6f92");

	cl_git_pass(git_commit_lookup(&commit, repo, &oid));

	opts.id = git_commit_id(commit);
	opts.author = git_commit_author(commit);
	opts.summary = git_commit_summary(commit);
	opts.patch_no = 2;
	opts.total_patches = 1;

	cl_git_pass(git_diff__commit(&diff, repo, commit, NULL));
	cl_git_fail(git_diff_format_email(&buf, diff, &opts));
	cl_git_fail(git_diff_commit_as_email(&buf, repo, commit, 2, 1, 0, NULL));
	cl_git_fail(git_diff_commit_as_email(&buf, repo, commit, 0, 0, 0, NULL));

	git_diff_free(diff);
	git_commit_free(commit);
	git_buf_free(&buf);
}
