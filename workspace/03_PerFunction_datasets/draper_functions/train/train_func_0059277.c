meta_set_byname(struct meta *meta, struct meta_node *node)
{
	int i;
	for (i = 0; i < meta->size; i++) {
		int cmp = strcmp(node->index_name, meta->nodes[i].index_name);
		if (cmp == 0) {
			memcpy(meta->nodes[i].end, node->end, SKIP_KSIZE);
			return ;
		}

	}
}
