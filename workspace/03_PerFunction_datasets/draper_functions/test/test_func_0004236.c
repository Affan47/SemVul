collection_remove_by_info(CollectionData *cd, CollectInfo *info)
{
	if (!info || !g_list_find(cd->list, info)) return;

	cd->list = g_list_remove(cd->list, info);
	cd->changed = (cd->list != NULL);

	collection_window_remove(collection_window_find(cd), info);
	collection_info_free(info);
}
