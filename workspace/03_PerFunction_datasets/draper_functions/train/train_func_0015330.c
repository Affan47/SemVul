podcast_update_thread(void * arg) {

	podcast_t * podcast = (podcast_t *)arg;
	podcast_download_t * pd;

	GSList * node;
	GTimeVal tval;
	GSList * list;

	AQUALUNG_THREAD_DETACH();

	if ((pd = podcast_download_new(podcast)) == NULL) {
		return NULL;
	}

	list = g_slist_copy(podcast->items);

	if (podcast_parse(podcast, &list) < 0) {
		goto finish;
	}

	list = g_slist_sort(list, podcast_item_compare_date);

	g_get_current_time(&tval);
	podcast->last_checked = tval.tv_sec;

	podcast_apply_limits(podcast, &list);

	for (node = list; node; node = node->next) {
		if (((podcast_item_t *)node->data)->file == NULL) {
			pd->ndownloads++;
		}
	}

	while (podcast_download_next(pd, &list)) {
		podcast_apply_limits(podcast, &list);
	}

 finish:
	g_slist_free(list);

	store_podcast_update_podcast(pd);

	return NULL;
}
