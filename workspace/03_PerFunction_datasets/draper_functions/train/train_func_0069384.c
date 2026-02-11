vcal_folder_get_webcal_events_for_folder(FolderItem *item)
{
	GetWebcalData *data = g_new0(GetWebcalData, 1);
	Folder *folder = folder_find_from_name ("vCalendar", vcal_folder_get_class());
	GSList *list = NULL;
	data->item = item;
	g_node_traverse(folder->node, G_PRE_ORDER,
			G_TRAVERSE_ALL, -1, get_webcal_events_func, data);

	list = data->list;
	g_free(data);

	return g_slist_reverse(list);
}
