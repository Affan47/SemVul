test_unref_reparent(void)
{
	void *root, *p1, *p2, *c1;

	printf("test: unref_reparent\n# UNREFERENCE AFTER PARENT FREED\n");

	root = talloc_named_const(NULL, 0, "root");
	p1 = talloc_named_const(root, 1, "orig parent");
	p2 = talloc_named_const(root, 1, "parent by reference");

	c1 = talloc_named_const(p1, 1, "child");
	talloc_reference(p2, c1);

	CHECK_PARENT("unref_reparent", c1, p1);

	talloc_free(p1);

	CHECK_PARENT("unref_reparent", c1, p2);

	talloc_unlink(p2, c1);

	CHECK_SIZE("unref_reparent", root, 1);

	talloc_free(p2);
	talloc_free(root);

	printf("success: unref_reparent\n");
	return true;
}
