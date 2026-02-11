parse_podcast_item(xmlDocPtr doc, xmlNodePtr cur, GtkTreeIter * pod_iter, podcast_t * podcast) {

	GtkTreeIter iter;
	podcast_item_t * item;
	char sort[MAXLEN];

	if ((item = podcast_item_new()) == NULL) {
		return;
	}

	podcast->items = g_slist_prepend(podcast->items, item);

	gtk_tree_store_append(music_store, &iter, pod_iter);
	gtk_tree_store_set(music_store, &iter,
			   MS_COL_NAME, "",
			   MS_COL_SORT, "",
			   MS_COL_DATA, item, -1);

	if (options.enable_ms_tree_icons) {
		gtk_tree_store_set(music_store, &iter, MS_COL_ICON, icon_track, -1);
	}

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {

		xml_load_str_dup(doc, cur, "file", &item->file);
		xml_load_str_dup(doc, cur, "title", &item->title);
		xml_load_str_dup(doc, cur, "desc", &item->desc);
		xml_load_str_dup(doc, cur, "url", &item->url);
		xml_load_str(doc, cur, "sort", sort);

		xml_load_int(doc, cur, "new", &item->new);
		xml_load_float(doc, cur, "duration", &item->duration);
		xml_load_uint(doc, cur, "size", &item->size);
		xml_load_uint(doc, cur, "date", &item->date);
	}

	if (item->new) {
		gtk_tree_store_set(music_store, &iter, MS_COL_FONT, PANGO_WEIGHT_BOLD, -1);
	}
	gtk_tree_store_set(music_store, &iter, MS_COL_NAME, item->title, -1);
	gtk_tree_store_set(music_store, &iter, MS_COL_SORT, sort, -1);
}
