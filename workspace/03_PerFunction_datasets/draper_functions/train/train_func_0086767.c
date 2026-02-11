save_podcast(xmlDocPtr doc, xmlNodePtr root, GtkTreeIter * pod_iter) {

	xmlNodePtr node;
	podcast_t * podcast;
	GtkTreeIter iter;
	int i;

	gtk_tree_model_get(GTK_TREE_MODEL(music_store), pod_iter, MS_COL_DATA, &podcast, -1);

	node = xmlNewTextChild(root, NULL, (const xmlChar *) "channel", NULL);
	xml_save_str(node, "dir", podcast->dir);
	xml_save_str(node, "title", podcast->title);
	xml_save_str(node, "author", podcast->author);
	xml_save_str(node, "desc", podcast->desc);
	xml_save_str(node, "url", podcast->url);

	xml_save_int(node, "flags", podcast->flags);
	xml_save_uint(node, "check_interval", podcast->check_interval);
	xml_save_uint(node, "last_checked", podcast->last_checked);
	xml_save_uint(node, "count_limit", podcast->count_limit);
	xml_save_uint(node, "date_limit", podcast->date_limit);
	xml_save_uint(node, "size_limit", podcast->size_limit);

	i = 0;
	while (gtk_tree_model_iter_nth_child(GTK_TREE_MODEL(music_store), &iter, pod_iter, i++)) {
		save_podcast_item(doc, node, &iter);
	}
}
