ldns_radix_array_reduce(ldns_radix_node_t* node)
{
	if (node->len <= node->capacity/2 && node->len != node->capacity) {
		ldns_radix_array_t* a = LDNS_XMALLOC(ldns_radix_array_t,
								node->len);
		if (!a) {
			return;
		}
		memcpy(a, node->array, sizeof(ldns_radix_array_t)*node->len);
		LDNS_FREE(node->array);
		node->array = a;
		node->capacity = node->len;
	}
	return;
}
