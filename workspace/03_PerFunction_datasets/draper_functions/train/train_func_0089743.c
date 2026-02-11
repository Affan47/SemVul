dcc_queue_remove_entry(int queue, int remove_head)
{
	DCC_QUEUE_REC *rec;
	GSList **qlist;

	g_assert(queue >= 0 && queue < queuelist->len);

	qlist = (GSList **) &g_ptr_array_index(queuelist, queue);
	if (*qlist == NULL || (*qlist)->next == NULL)
		return 0;

	rec = remove_head ? (*qlist)->data : g_slist_last(*qlist)->data;
	*qlist = g_slist_remove(*qlist, rec);

	dcc_queue_free_rec(rec);
	return 1;
}
