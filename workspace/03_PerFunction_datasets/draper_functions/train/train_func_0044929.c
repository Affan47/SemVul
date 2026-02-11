ldns_radix_first(ldns_radix_t* tree)
{
	ldns_radix_node_t* first = NULL;
	if (!tree || !tree->root) {
		return NULL;
	}
	first = tree->root;
	if (first->data) {
		return first;
	}
	return ldns_radix_next(first);
}
