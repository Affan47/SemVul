parq_save_timer(void *unused_udata)
{
	(void) unused_udata;

	if (!parq_is_enabled())
		return TRUE;

	if (GNET_PROPERTY(parq_debug)) {
		GList *l;

		for (l = ul_parqs ; l != NULL; l = g_list_next(l)) {
			struct parq_ul_queue *q = l->data;

			g_debug("PARQ UL: Queue %d/%d contains %d items, "
				  "%d uploading, %d alive, queue marked %s",
				  q->num, ul_parqs_cnt, q->by_position_length,
				  q->active_uploads, q->alive,
				  q->active ? "active" : "inactive");
		}
	}

	parq_upload_save_queue();

	return TRUE;
}
