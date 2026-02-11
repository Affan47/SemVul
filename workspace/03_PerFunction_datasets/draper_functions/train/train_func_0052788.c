dupe_check_start(DupeWindow *dw)
{
	dw->setup_done = FALSE;

	dw->setup_count = g_list_length(dw->list);
	if (dw->second_set) dw->setup_count += g_list_length(dw->second_list);

	dw->setup_mask = 0;
	dupe_setup_reset(dw);

	dw->working = g_list_last(dw->list);

	dupe_window_update_count(dw, TRUE);
	widget_set_cursor(dw->listview, GDK_WATCH);

	if (dw->idle_id) return;

	dw->idle_id = g_idle_add(dupe_check_cb, dw);
}
