nautilus_file_changes_queue_add_common (NautilusFileChangesQueue *queue,
	NautilusFileChange *new_item)
{

	g_mutex_lock (&queue->mutex);

	queue->head = g_list_prepend (queue->head, new_item);
	if (queue->tail == NULL)
		queue->tail = queue->head;

	g_mutex_unlock (&queue->mutex);
}
