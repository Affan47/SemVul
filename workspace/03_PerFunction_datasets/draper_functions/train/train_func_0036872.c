result_item_multi_create(GtkTextTagTable * table)
{
	result_item_t *item = calloc(1, sizeof(*item));
	if (item == NULL) {
		return item;
	}
	if (single_buffer == NULL) {
		single_buffer = gtk_text_buffer_new(table);
	}
	item->supported = 1;
	item->destructor = result_item_multi_destructor;
	item->policy_changed = result_item_multi_policy_changed;
	item->poldiff_run = result_item_multi_poldiff_run;
	item->get_buffer = result_item_multi_get_buffer;
	item->is_render_slow = result_item_multi_is_render_slow;
	item->get_forms = result_item_role_trans_get_forms;
	item->set_current_sort = result_item_multi_set_current_sort;
	int i;
	for (i = 0; i < 5; i++) {
		item->data.multi.buffers[i] = gtk_text_buffer_new(table);
		item->sorts[i] = RESULTS_SORT_DEFAULT;
		item->sort_dirs[i] = RESULTS_SORT_ASCEND;
	}
	return item;
}
