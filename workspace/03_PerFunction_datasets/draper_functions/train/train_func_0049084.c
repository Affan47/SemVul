circle_link_traversal(struct circle_link *link, void *data, circle_link_handler_t handler)
{
	struct single_link_node *head, *node;

	pthread_mutex_lock(&link->lock);

	for (head = &link->head_node, node = head->next; node != head; node = node->next)
	{
		handler(link, node, data);
	}

	pthread_mutex_unlock(&link->lock);
}
