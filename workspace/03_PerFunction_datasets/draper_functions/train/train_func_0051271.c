que_remove_node_by_data(que_t * q,  char * pc_data)
{

	node_t * prev;
	node_t * node;
	char * pc_ret_data;

	node = q->list;
	prev = q->list;

	if (0 == q->amount)
	{

		return NULL;
	}

	while (node)
	{
		if (node->pc_data == pc_data )
		{

			if (q->list == node)
			{
				q->list = node->next;
				if (q->tail == node) q->tail = q->list;
			}
			else
			{
				prev = node->next;
				if (q->tail == node) q->tail = prev;
			}

			pc_ret_data = node->pc_data;

			free(node);
			q->amount--;
			return(pc_ret_data);
		}

		prev = node;
		node = node->next;
	}

    return(NULL);
}
