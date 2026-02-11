main (int argc, char* argv[])
{
	struct rooted_tree *tree;
	struct parameters params;

	params = get_params(argc, argv);

	while ((tree = parse_tree()) != NULL) {
		process_tree(tree, params);
		destroy_tree(tree);
		destroy_all_rnodes(NULL);
	}

	return 0;
}
