exporthtml_sort_email( const GList *list ) {
	const GList *node;
	GList *sorted = NULL;

	node = list;
	while( node ) {
		sorted = g_list_insert_sorted(
				sorted, node->data, exporthtml_compare_email );
		node = g_list_next( node );
	}
	return sorted;
}
