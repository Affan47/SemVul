binary_tree_free_node(struct binary_tree_descriptor *desc, struct binary_tree_node *node)
{
	if ((struct binary_tree_cache *) node >= desc->buff && (struct binary_tree_cache *) node < desc->buff_end)
	{
		((struct binary_tree_cache *) node)->flags = 0;
	}
	else
	{
		free(node);
	}
}
