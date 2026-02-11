_gtk_print_key_pairs(List config_list, char *title, bool first,
				 GtkTreeStore *treestore, GtkTreeIter *iter)
{
	ListIterator itr = NULL;
	config_key_pair_t *key_pair;
	int update = 0;

	if (!config_list || !list_count(config_list))
		return;

	if (!first)
		add_display_treestore_line(update, treestore, iter, "", NULL);

	add_display_treestore_line_with_font(update, treestore, iter,
					     title, NULL, "bold");

	itr = list_iterator_create(config_list);
	while ((key_pair = list_next(itr)))
		add_display_treestore_line(update, treestore, iter,
					   key_pair->name, key_pair->value);
	list_iterator_destroy(itr);
}
