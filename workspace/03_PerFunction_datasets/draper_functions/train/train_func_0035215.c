free_node(struct fuse *f, struct node *node)
{
	if (node->name != node->inline_name)
		free(node->name);
	free_node_mem(f, node);
}
