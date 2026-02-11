test_realloc_fn(void)
{
	void *root, *p1;

	printf("test: realloc_fn\n# talloc_realloc_fn\n");

	root = talloc_new(NULL);

	p1 = talloc_realloc_fn(root, NULL, 10);
	CHECK_BLOCKS("realloc_fn", root, 2);
	CHECK_SIZE("realloc_fn", root, 10);
	p1 = talloc_realloc_fn(root, p1, 20);
	CHECK_BLOCKS("realloc_fn", root, 2);
	CHECK_SIZE("realloc_fn", root, 20);
	p1 = talloc_realloc_fn(root, p1, 0);
	CHECK_BLOCKS("realloc_fn", root, 1);
	CHECK_SIZE("realloc_fn", root, 0);

	talloc_free(root);

	printf("success: realloc_fn\n");
	return true;
}
