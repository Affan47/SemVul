test_refs_iterator__list(void)
{
	git_reference_iterator *iter;
	git_vector output;
	git_reference *ref;
	int error;
	size_t i;

	cl_git_pass(git_vector_init(&output, 32, &refcmp_cb));
	cl_git_pass(git_reference_iterator_new(&iter, repo));

	do {
		error = git_reference_next(&ref, iter);
		cl_assert(error == 0 || error == GIT_ITEROVER);
		if (error != GIT_ITEROVER) {
			cl_git_pass(git_vector_insert(&output, ref));
		}
	} while (!error);

	git_reference_iterator_free(iter);
	cl_assert_equal_sz(output.length, ARRAY_SIZE(refnames));

	git_vector_sort(&output);

	git_vector_foreach(&output, i, ref) {
		cl_assert_equal_s(ref->name, refnames[i]);
		git_reference_free(ref);
	}

	git_vector_free(&output);
}
