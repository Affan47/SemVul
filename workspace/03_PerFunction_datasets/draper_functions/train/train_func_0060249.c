DOODLE_tree_dump(FILE * stream,
		     SuffixTree * tree) {
  CHECK(tree);
  if ( (tree == NULL) ||
       (stream == NULL) )
    return 1;
  return print_internal(tree,
			tree->root,
			stream,
			2);
}
