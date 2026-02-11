iterate_refs(void *arg)
{
	git_reference_iterator *i;
	git_reference *ref;
	int count = 0;

	cl_git_pass(git_reference_iterator_new(&i, g_repo));

	for (count = 0; !git_reference_next(&ref, i); ++count) {
		cl_assert(ref != NULL);
		git_reference_free(ref);
	}

	if (g_expected > 0)
		cl_assert_equal_i(g_expected, count);

	git_reference_iterator_free(i);

	giterr_clear();
	return arg;
}
