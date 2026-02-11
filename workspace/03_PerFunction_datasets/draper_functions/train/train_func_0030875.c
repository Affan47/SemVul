test_object_blob_filter__to_odb(void)
{
	git_filter_list *fl = NULL;
	git_config *cfg;
	int i;
	git_blob *blob;
	git_buf out = GIT_BUF_INIT, zeroed;

	cl_git_pass(git_repository_config(&cfg, g_repo));
	cl_assert(cfg);

	git_attr_cache_flush(g_repo);
	cl_git_append2file("empty_standard_repo/.gitattributes", "*.txt text\n");

	cl_git_pass(git_filter_list_load(
		&fl, g_repo, NULL, "filename.txt", GIT_FILTER_TO_ODB, 0));
	cl_assert(fl != NULL);

	for (i = 0; i < CRLF_NUM_TEST_OBJECTS; i++) {
		cl_git_pass(git_blob_lookup(&blob, g_repo, &g_crlf_oids[i]));


		cl_git_pass(git_filter_list_apply_to_blob(&out, fl, blob));
		cl_assert_equal_sz(g_crlf_filtered[i].size, out.size);
		cl_assert_equal_i(
			0, memcmp(out.ptr, g_crlf_filtered[i].ptr, out.size));


		memset(&zeroed, 0, sizeof(zeroed));
		cl_git_pass(git_filter_list_apply_to_blob(&zeroed, fl, blob));
		cl_assert_equal_sz(g_crlf_filtered[i].size, zeroed.size);
		cl_assert_equal_i(
			0, memcmp(zeroed.ptr, g_crlf_filtered[i].ptr, zeroed.size));
		git_buf_free(&zeroed);

		git_blob_free(blob);
	}

	git_filter_list_free(fl);
	git_buf_free(&out);
	git_config_free(cfg);
}
