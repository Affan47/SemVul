ldns_radix_node_array_free(ldns_radix_node_t* node)
{
	node->offset = 0;
	node->len = 0;
	LDNS_FREE(node->array);
	node->array = NULL;
	node->capacity = 0;
	return;
}
