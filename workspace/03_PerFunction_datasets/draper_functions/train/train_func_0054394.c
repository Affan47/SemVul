tree_search(struct rb_root *root, u64 bytenr)
{
	struct rb_node *n = root->rb_node;
	struct tree_entry *entry;

	while (n) {
		entry = rb_entry(n, struct tree_entry, rb_node);

		if (bytenr < entry->bytenr)
			n = n->rb_left;
		else if (bytenr > entry->bytenr)
			n = n->rb_right;
		else
			return n;
	}
	return NULL;
}
