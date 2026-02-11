prv_free_cb(gpointer data)
{
	dleyna_task_queue_t *task_queue = data;

	DLEYNA_LOG_DEBUG("Enter");

	g_ptr_array_foreach(task_queue->tasks, prv_task_free_cb, task_queue);
	g_ptr_array_unref(task_queue->tasks);

	if (task_queue->task_queue_finally_cb)
		task_queue->task_queue_finally_cb(task_queue->cancelled,
						  task_queue->user_data);

	g_free(task_queue);

	DLEYNA_LOG_DEBUG("Exit");
}
