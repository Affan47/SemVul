enqueue (ETableHeader *eth,
         gint column,
         gint width)
{
	struct two_ints *store;
	store = g_new (struct two_ints, 1);
	store->column = column;
	store->width = width;

	eth->change_tail = g_slist_last (g_slist_append (eth->change_tail, store));
	if (!eth->change_queue)
		eth->change_queue = eth->change_tail;

	if (!eth->idle) {
		eth->idle = g_idle_add_full (
			G_PRIORITY_LOW, (GSourceFunc)
			dequeue_idle, eth, NULL);
	}
}
