brasero_file_node_insert (BraseroFileNode *head,
			  BraseroFileNode *node,
			  GCompareFunc sort_func,
			  guint *newpos)
{
	BraseroFileNode *iter;
	guint n = 0;


	if (!head) {
		node->next = NULL;
		return node;
	}


	if (head->is_hidden) {
		node->next = head;
		if (newpos)
			*newpos = 0;

		return node;
	}

	if (node->is_hidden) {
		iter = head;
		n = 1;
		while (iter->next)  {
			iter = iter->next;
			n ++;
		}

		iter->next = node;

		if (newpos)
			*newpos = n;

		return head;
	}


	if (sort_func (head, node) > 0) {

		node->next = head;
		if (newpos)
			*newpos = 0;

		return node;
	}

	n = 1;
	for (iter = head; iter->next; iter = iter->next) {
		if (sort_func (iter->next, node) > 0) {

			node->next = iter->next;
			iter->next = node;

			if (newpos)
				*newpos = n;

			return head;
		}
		n ++;
	}


	iter->next = node;
	node->next = NULL;

	if (newpos)
		*newpos = n;

	return head;
}
