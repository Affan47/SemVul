collect_manager_entry_free_data(CollectManagerEntry *entry)
{
	GList *work;

	work = entry->add_list;
	while (work)
		{
		CollectManagerAction *action;

		action = work->data;
		work = work->next;

		collect_manager_action_unref(action);
		}
	g_list_free(entry->add_list);
	g_hash_table_destroy(entry->oldpath_hash);
	g_hash_table_destroy(entry->newpath_hash);
}
