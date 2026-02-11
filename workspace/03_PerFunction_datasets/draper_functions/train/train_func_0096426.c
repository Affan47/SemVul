crush_remove_tree_bucket_item(struct crush_bucket_tree *bucket, int item)
{
	unsigned i;
	unsigned newsize;

	for (i = 0; i < bucket->h.size; i++) {
		int node;
		int weight;
		int j;
		int depth = calc_depth(bucket->h.size);

		if (bucket->h.items[i] != item)
			continue;

		node = crush_calc_tree_node(i);
		weight = bucket->node_weights[node];
		bucket->node_weights[node] = 0;

		for (j = 1; j < depth; j++) {
			node = parent(node);
			bucket->node_weights[node] -= weight;
			printf(" node %d weight %d\n", node, bucket->node_weights[node]);
		}
		bucket->h.weight -= weight;
		break;
	}
	if (i == bucket->h.size)
		return -ENOENT;

	newsize = bucket->h.size;
	while (newsize > 0) {
		int node = crush_calc_tree_node(newsize - 1);
		if (bucket->node_weights[node])
			break;
		--newsize;
	}

	if (newsize != bucket->h.size) {
		int olddepth, newdepth;

		void *_realloc = NULL;

		if ((_realloc = realloc(bucket->h.items, sizeof(__s32)*newsize)) == NULL) {
			return -ENOMEM;
		} else {
			bucket->h.items = _realloc;
		}
		if ((_realloc = realloc(bucket->h.perm, sizeof(__u32)*newsize)) == NULL) {
			return -ENOMEM;
		} else {
			bucket->h.perm = _realloc;
		}

		olddepth = calc_depth(bucket->h.size);
		newdepth = calc_depth(newsize);
		if (olddepth != newdepth) {
			bucket->num_nodes = 1 << newdepth;
			if ((_realloc = realloc(bucket->node_weights,
						sizeof(__u32)*bucket->num_nodes)) == NULL) {
				return -ENOMEM;
			} else {
				bucket->node_weights = _realloc;
			}
		}

		bucket->h.size = newsize;
	}
	return 0;
}
