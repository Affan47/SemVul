test_core_pool__0(void)
{
	int i;
	git_pool p;
	void *ptr;

	cl_git_pass(git_pool_init(&p, 1, 4000));

	for (i = 1; i < 10000; i *= 2) {
		ptr = git_pool_malloc(&p, i);
		cl_assert(ptr != NULL);
		cl_assert(git_pool__ptr_in_pool(&p, ptr));
		cl_assert(!git_pool__ptr_in_pool(&p, &i));
	}


	cl_assert(git_pool__open_pages(&p) + git_pool__full_pages(&p) == 4);

	git_pool_clear(&p);
}
