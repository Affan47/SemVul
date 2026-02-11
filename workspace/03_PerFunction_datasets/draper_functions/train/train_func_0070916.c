nautilus_file_queue_enqueue (NautilusFileQueue *queue,
			     NautilusFile      *file)
{
	if (g_hash_table_lookup (queue->item_to_link_map, file) != NULL) {

		return;
	}

	if (queue->tail == NULL) {
		queue->head = g_list_append (NULL, file);
		queue->tail = queue->head;
	} else {
		queue->tail = g_list_append (queue->tail, file);
		queue->tail = queue->tail->next;
	}

	nautilus_file_ref (file);
	g_hash_table_insert (queue->item_to_link_map, file, queue->tail);
}
