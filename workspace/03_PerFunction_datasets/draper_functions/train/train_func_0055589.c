tree_iterator_test(
	const char *sandbox,
	const char *treeish,
	const char *start,
	const char *end,
	int expected_count,
	const char **expected_values)
{
	git_tree *t;
	git_iterator *i;
	const git_index_entry *entry;
	int count = 0, count_post_reset = 0;
	git_repository *repo = cl_git_sandbox_init(sandbox);

	cl_assert(t = resolve_commit_oid_to_tree(repo, treeish));
	cl_git_pass(git_iterator_for_tree(
		&i, t, GIT_ITERATOR_DONT_IGNORE_CASE, start, end));


	cl_git_pass(git_iterator_current(&entry, i));
	while (entry != NULL) {
		if (expected_values != NULL)
			cl_assert_equal_s(expected_values[count], entry->path);
		count++;
		cl_git_pass(git_iterator_advance(&entry, i));
	}


	cl_git_pass(git_iterator_reset(i, NULL, NULL));
	cl_git_pass(git_iterator_current(&entry, i));
	while (entry != NULL) {
		if (expected_values != NULL)
			cl_assert_equal_s(expected_values[count_post_reset], entry->path);
		count_post_reset++;
		cl_git_pass(git_iterator_advance(&entry, i));
	}

	git_iterator_free(i);

	cl_assert_equal_i(expected_count, count);
	cl_assert_equal_i(count, count_post_reset);

	git_tree_free(t);
}
