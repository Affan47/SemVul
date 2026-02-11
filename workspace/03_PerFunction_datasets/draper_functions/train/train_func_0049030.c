ets_dispose (GObject *object)
{
	ETableSorted *ets = E_TABLE_SORTED (object);

	if (ets->sort_idle_id)
		g_source_remove (ets->sort_idle_id);
	ets->sort_idle_id = 0;

	if (ets->insert_idle_id)
		g_source_remove (ets->insert_idle_id);
	ets->insert_idle_id = 0;

	if (ets->sort_info) {
		g_signal_handler_disconnect (
			ets->sort_info,
			ets->sort_info_changed_id);
		g_object_unref (ets->sort_info);
		ets->sort_info = NULL;
	}

	if (ets->full_header)
		g_object_unref (ets->full_header);
	ets->full_header = NULL;

	G_OBJECT_CLASS (e_table_sorted_parent_class)->dispose (object);
}
