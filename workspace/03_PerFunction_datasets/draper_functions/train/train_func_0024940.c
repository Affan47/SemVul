navqueue_free()
{
	while (! g_queue_is_empty(navigation_queue))
	{
		g_free(g_queue_pop_tail(navigation_queue));
	}
	g_queue_free(navigation_queue);
}
