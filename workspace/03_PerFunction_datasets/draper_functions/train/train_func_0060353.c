parq_upload_recompute_queue_num(void)
{
	GList *l;
	int pos = 0;

	for (l = ul_parqs; l; l = g_list_next(l)) {
		struct parq_ul_queue *q = l->data;

		q->num = ++pos;
	}
}
