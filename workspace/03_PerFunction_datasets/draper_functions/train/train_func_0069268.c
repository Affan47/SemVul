double_link_find_base(struct double_link *link, void *data, double_link_matcher_t matcher)
{
	struct double_link_node *head, *node;

	for (head = &link->head_node, node = head->next; node != head; node = node->next)
	{
		if (matcher(link, node, data))
		{
			return node;
		}
	}

	return NULL;
}
