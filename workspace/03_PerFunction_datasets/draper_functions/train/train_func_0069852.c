test_index_reuc__retained_on_reset_soft(void)
{
	git_object *target;

	retrieve_target_from_oid(&target, repo, "3a34580a35add43a4cf361e8e9a30060a905c876");

	git_reset(repo, target, GIT_RESET_HARD);

	test_index_reuc__add();
	cl_git_pass(git_reset(repo, target, GIT_RESET_SOFT));
	cl_assert(reuc_entry_exists() == true);

	git_object_free(target);
}
