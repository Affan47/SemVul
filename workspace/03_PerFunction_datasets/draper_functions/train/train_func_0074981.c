test_talloc_free_in_destructor(void)
{
	void *level0;
	void *level1;
	void *level2;
	void *level3;
	void *level4;
	void **level5;

	printf("test: free_in_destructor\n# TALLOC FREE IN DESTRUCTOR\n");

	level0 = talloc_new(NULL);
	level1 = talloc_new(level0);
	level2 = talloc_new(level1);
	level3 = talloc_new(level2);
	level4 = talloc_new(level3);
	level5 = talloc(level4, void *);

	*level5 = level3;
	(void)talloc_reference(level0, level3);
	(void)talloc_reference(level3, level3);
	(void)talloc_reference(level5, level3);

	talloc_set_destructor(level5, _test_talloc_free_in_destructor);

	talloc_free(level1);

	talloc_free(level0);

	printf("success: free_in_destructor\n");
	return true;
}
