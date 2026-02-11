grecs_node_unlink(struct grecs_node *node)
{
	if (node->prev)
		node->prev->next = node->next;
	else if (node->up)
		node->up->down = node->next;
	else
		return 1;
	if (node->next)
		node->next->prev = node->prev;
	return 0;
}
