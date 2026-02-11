main(int argc, char *argv[])
{
	struct rooted_tree *tree;
	struct parameters params;

	params = get_params(argc, argv);
	while (NULL != (tree = parse_tree())) {


		process_tree(tree, params);
	}

	destroy_llist(params.labels);
	return 0;
}
