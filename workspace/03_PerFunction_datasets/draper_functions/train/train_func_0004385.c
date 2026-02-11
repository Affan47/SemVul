replace_extent_mapping(struct extent_map_tree *tree,
			    struct extent_map *cur,
			    struct extent_map *new,
			    int modified)
{
	WARN_ON(test_bit(EXTENT_FLAG_PINNED, &cur->flags));
	ASSERT(extent_map_in_tree(cur));
	if (!test_bit(EXTENT_FLAG_LOGGING, &cur->flags))
		list_del_init(&cur->list);
	rb_replace_node(&cur->rb_node, &new->rb_node, &tree->map);
	RB_CLEAR_NODE(&cur->rb_node);

	setup_extent_mapping(tree, new, modified);
}
