git_oid_shorten_add(git_oid_shorten *os, const char *text_oid)
{
	int i, is_leaf;
	node_index idx;

	if (os->full)
		return GIT_ENOMEM;

	if (text_oid == NULL)
		return os->min_length;

	idx = 0;
	is_leaf = 0;

	for (i = 0; i < GIT_OID_HEXSZ; ++i) {
		int c = from_hex[(int)text_oid[i]];
		trie_node *node;

		if (c == -1)
			return git__throw(GIT_ENOTOID, "Failed to shorten OID. Invalid hex value");

		node = &os->nodes[idx];

		if (is_leaf) {
			const char *tail;

			tail = node->tail;
			node->tail = NULL;

			node = push_leaf(os, idx, from_hex[(int)tail[0]], &tail[1]);
			if (node == NULL)
				return GIT_ENOMEM;
		}

		if (node->children[c] == 0) {
			if (push_leaf(os, idx, c, &text_oid[i + 1]) == NULL)
				return GIT_ENOMEM;
			break;
		}

		idx = node->children[c];
		is_leaf = 0;

		if (idx < 0) {
			node->children[c] = idx = -idx;
			is_leaf = 1;
		}
	}

	if (++i > os->min_length)
		os->min_length = i;

	return os->min_length;
}
