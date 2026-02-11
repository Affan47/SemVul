podcast_list_remove_item(podcast_t * podcast, GSList * list, GSList * litem) {

	podcast_item_t * item = (podcast_item_t *)litem->data;

	if (item->file) {
		if (unlink(item->file) < 0) {
			fprintf(stderr, "unlink: unable to unlink %s\n", item->file);
			perror("unlink");
		}

		podcast->items = g_slist_remove(podcast->items, item);
		store_podcast_remove_item(podcast, item);
	} else {
		podcast_item_free(item);
	}

	return g_slist_delete_link(list, litem);
}
