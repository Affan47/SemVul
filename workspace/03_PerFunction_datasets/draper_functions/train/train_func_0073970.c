flush_chunk_node_recursive(struct chunk_node *cnode, unsigned height)
{
	struct chunk_node *child;
	unsigned i;
	int err;

	if (height) {
		for (i = 0; i < DIGESTS_PER_CHUNK; i ++) {
			child = children_of(cnode)[i];
			if (!child)
				continue;
			err = flush_chunk_node_recursive(child, height - 1);
			if (err < 0)
				return err;
		}
	}

	return flush_chunk_node(cnode);
}
