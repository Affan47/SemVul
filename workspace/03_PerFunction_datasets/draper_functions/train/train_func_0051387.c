dleyna_task_queue_add_task(const dleyna_task_queue_key_t *queue_id,
				dleyna_task_atom_t *task)
{
	dleyna_task_queue_t *queue;

	DLEYNA_LOG_DEBUG("Enter - Task added to queue <%s,%s>",
			 queue_id->source, queue_id->sink);

	queue = g_hash_table_lookup(queue_id->processor->task_queues, queue_id);

	task->queue_id = queue_id;
	g_ptr_array_add(queue->tasks, task);

	if (queue->defer_remove)
		goto exit;

	if ((queue->flags & DLEYNA_TASK_QUEUE_FLAG_AUTO_START) &&
	    (!queue->current_task && !queue->idle_id))
		queue->idle_id = g_idle_add(prv_process_task,
					    (gpointer)queue_id);

exit:
	DLEYNA_LOG_DEBUG("Exit");
}
