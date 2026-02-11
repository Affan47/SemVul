count_generated_nodes (GArray *group)
{
	gint accum_offset = 0;
	gint i;

	for (i = 0; i < group->len; i++) {
		Node *node = &g_array_index (group, Node, i);

		accum_offset += node->n_generated;
	}

	return accum_offset;
}
