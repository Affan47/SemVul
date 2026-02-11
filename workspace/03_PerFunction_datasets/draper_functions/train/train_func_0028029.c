exotic_add_test(struct exotic_handle* handle, exo_test_t func, const char* name)
{
	struct exo_test_data* test;
	if (!handle)
	{
		fprintf(stderr, "exotic_add_test: failed, no handle!\n");
		exit(-1);
	}

	test = (struct exo_test_data*) malloc(sizeof(struct exo_test_data));
	if (!test)
	{
		fprintf(stderr, "exotic_add_test: out of memory!\n");
		exit(-1);
	}


	memset(test, 0, sizeof(struct exo_test_data));
	test->test = func;
	test->name = strdup(name);


	if (!handle->first)
	{
		handle->first = test;
		handle->current = test;
	}
	else
	{
		handle->current->next = test;
		handle->current = test;
	}
}
