test_stash_drop__dropping_the_top_stash_updates_the_stash_reference(void)
{
	git_object *next_top_stash;
	git_oid oid;

	push_three_states();

	retrieve_top_stash_id(&oid);

	cl_git_pass(git_revparse_single(&next_top_stash, repo, "stash@{1}"));
	cl_assert_equal_i(false, git_oid_cmp(&oid, git_object_id(next_top_stash)) == 0);

	cl_git_pass(git_stash_drop(repo, 0));

	retrieve_top_stash_id(&oid);

	cl_git_pass(git_oid_cmp(&oid, git_object_id(next_top_stash)));

	git_object_free(next_top_stash);
}
