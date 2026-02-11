e_intervaltree_search (EIntervalTree *tree,
                       time_t start,
                       time_t end)
{
	EIntervalNode *node;
	GList *list = NULL;
	GList *stack_start = NULL, *pos;

	g_return_val_if_fail (E_IS_INTERVALTREE (tree), NULL);

	g_rec_mutex_lock (&tree->priv->mutex);

	stack_start = pos = g_list_insert (
		stack_start, tree->priv->root->left, -1);

	while (pos != NULL) {
		node = (EIntervalNode *) pos->data;

		if (node != tree->priv->nil) {
			if (compare_intervals (node->start, node->end, start, end) == 0) {
				list = g_list_insert (list, node->comp, -1);
				g_object_ref (node->comp);
			}

			if (compare_intervals (node->left->min, node->left->max, start, end) == 0)
				pos = g_list_insert (pos, node->left, -1);

			if (compare_intervals (node->right->min, node->right->max, start, end) == 0)
				pos = g_list_insert (pos, node->right, -1);
		}

		pos = pos->next;
	}

	g_list_free (stack_start);

	g_rec_mutex_unlock (&tree->priv->mutex);

	return list;
}
