bch_btree_keys_free(struct btree_keys *b)
{
	struct bset_tree *t = b->set;

	if (bset_prev_bytes(b) < PAGE_SIZE)
		kfree(t->prev);
	else
		free_pages((unsigned long) t->prev,
			   get_order(bset_prev_bytes(b)));

	if (bset_tree_bytes(b) < PAGE_SIZE)
		kfree(t->tree);
	else
		free_pages((unsigned long) t->tree,
			   get_order(bset_tree_bytes(b)));

	free_pages((unsigned long) t->data, b->page_order);

	t->prev = NULL;
	t->tree = NULL;
	t->data = NULL;
}
