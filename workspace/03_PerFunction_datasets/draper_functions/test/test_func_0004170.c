circle_link_find(struct circle_link *link, void *data, circle_link_matcher_t matcher)
{
	struct single_link_node *head, *node;

	pthread_mutex_lock(&link->lock);

	for (head = &link->head_node, node = head->next; node != head; node = node->next)
	{
		if (matcher(link, node, data))
		{
			pthread_mutex_unlock(&link->lock);

			return node;
		}
	}

	pthread_mutex_unlock(&link->lock);

	return NULL;
}
