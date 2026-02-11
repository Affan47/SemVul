print_internal(SuffixTree * tree,
			  STNode * node,
			  FILE * stream,
			  int ident) {
  int i;

  CHECK(tree);
  while (node != NULL) {
    fprintf(stream,
	    "%*c%.*s:\n",
	    ident,
	    ' ',
	    (int)node->clength,
	    node->c);
    for (i=node->matchCount-1;i>=0;i--)
      fprintf(stream,
	      "%*c  %s\n",
	      ident,
	      ' ',
	      tree->filenames[node->matches[i]].filename);
    if ( (node->child == NULL) &&
	 (node->next_off != 0) )
      if (-1 == loadChild(tree,
			  node))
	return -1;
    print_internal(tree,
		   node->child,
		   stream,
		   ident+2);
    if ( (node->link == NULL) &&
	 (node->link_off != 0) )
      if (-1 == loadLink(tree,
			 node))
	return -1;
    node = node->link;
  }
  return 0;
}
