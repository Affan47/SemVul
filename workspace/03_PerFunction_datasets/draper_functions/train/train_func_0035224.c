test_pack_packbuilder__foreach_with_cancel(void)
{
	git_indexer *idx;

	seed_packbuilder();
	cl_git_pass(git_indexer_new(&idx, ".", 0, NULL, NULL, NULL));
	cl_git_fail_with(
		git_packbuilder_foreach(_packbuilder, foreach_cancel_cb, idx), -1111);
	git_indexer_free(idx);
}
