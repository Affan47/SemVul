tracker_priority_queue_foreach (TrackerPriorityQueue *queue,
                                GFunc                 func,
                                gpointer              user_data)
{
	g_return_if_fail (queue != NULL);
	g_return_if_fail (func != NULL);

	g_queue_foreach (&queue->queue, func, user_data);
}
