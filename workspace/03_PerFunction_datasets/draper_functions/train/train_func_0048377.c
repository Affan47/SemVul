find_delalloc_range(struct extent_io_tree *tree,
					u64 *start, u64 *end, u64 max_bytes,
					struct extent_state **cached_state)
{
	struct rb_node *node;
	struct extent_state *state;
	u64 cur_start = *start;
	u64 found = 0;
	u64 total_bytes = 0;

	spin_lock(&tree->lock);


	node = tree_search(tree, cur_start);
	if (!node) {
		if (!found)
			*end = (u64)-1;
		goto out;
	}

	while (1) {
		state = rb_entry(node, struct extent_state, rb_node);
		if (found && (state->start != cur_start ||
			      (state->state & EXTENT_BOUNDARY))) {
			goto out;
		}
		if (!(state->state & EXTENT_DELALLOC)) {
			if (!found)
				*end = state->end;
			goto out;
		}
		if (!found) {
			*start = state->start;
			*cached_state = state;
			atomic_inc(&state->refs);
		}
		found++;
		*end = state->end;
		cur_start = state->end + 1;
		node = rb_next(node);
		total_bytes += state->end - state->start + 1;
		if (total_bytes >= max_bytes)
			break;
		if (!node)
			break;
	}
out:
	spin_unlock(&tree->lock);
	return found;
}
