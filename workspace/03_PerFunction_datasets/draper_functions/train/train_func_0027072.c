authcookie_destroy(authcookie_t * ac)
{
	return_if_fail(ac != NULL);

	mowgli_node_delete(&ac->node, &authcookie_list);
	free(ac->ticket);
	mowgli_heap_free(authcookie_heap, ac);
}
