get_first_visible_index_from (GArray *group,
                              gint index)
{
	gint i;

	for (i = index; i < group->len; i++) {
		Node *node = &g_array_index (group, Node, i);

		if (node->n_generated)
			break;
	}

	if (i >= group->len)
		i = -1;

	return i;
}
