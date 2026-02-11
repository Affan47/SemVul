test_revwalk_basic__push_head_hide_ref(void)
{
	int i = 0;
	git_oid oid;

	cl_git_pass(git_revwalk_push_head(_walk));
	cl_git_pass(git_revwalk_hide_ref(_walk, "refs/heads/packed-test"));

	while (git_revwalk_next(&oid, _walk) == 0) {
		i++;
	}


	cl_assert(i == 4);
}
