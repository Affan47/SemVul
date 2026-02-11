main() {
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;

	node_t* n1 = node(&data1);
	node_t* n2 = node(&data2);

	node_t* parent = node_append(NULL, n1, n2);
	parent->data = &data3;

	tree_traverse(parent, 0, sum_callback);

	printf("the total is %d\n", sum);

	node_t* test_is_leaf = node(NULL);
	node_t* test_is_not_leaf_left = node_append(NULL, parent, NULL);

	fprintf(stdout, " expected 1: %d\n", node_is_leaf(*test_is_leaf));
	fprintf(stdout, " expected 0: %d\n",
		node_is_leaf(*test_is_not_leaf_left));

	tree_free(parent);

	return 0;
}
