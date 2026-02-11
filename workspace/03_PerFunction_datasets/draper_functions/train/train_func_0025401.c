lt_trie_node_remove(lt_trie_node_t *node,
		    lt_trie_node_t *parent,
		    const char     *key)
{
	int i, index_;
	lt_bool_t found = FALSE;

	lt_return_val_if_fail (node != NULL, FALSE);
	lt_return_val_if_fail (key != NULL, FALSE);

	index_ = (unsigned char)*key - 1;
	if (*key == 0) {
		if (!node->data)
			return FALSE;
		lt_mem_delete_ref(&node->parent, node->data);
		node->data = NULL;
		for (i = 0; i < 255; i++) {
			found |= node->node[i] != NULL;
		}
		if (!found)
			lt_mem_delete_ref(&parent->parent, node);
		return TRUE;
	}
	if (!node->node[index_])
		return FALSE;

	return lt_trie_node_remove(node->node[index_], node, key + 1);
}
