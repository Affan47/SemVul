collection_insert(CollectionData *cd, FileData *fd, CollectInfo *insert_ci, gboolean sorted)
{
	struct stat st;

	if (!insert_ci) return collection_add(cd, fd, sorted);

	if (stat_utf8(fd->path, &st) >= 0 && !S_ISDIR(st.st_mode))
		{
		CollectInfo *ci;

		ci = collection_info_new_if_not_exists(cd, &st, fd);
		if (!ci) return FALSE;

		DEBUG_3("insert in collection: %s", fd->path);

		cd->list = collection_list_insert(cd->list, ci, insert_ci, sorted ? cd->sort_method : SORT_NONE);
		cd->changed = TRUE;

		collection_window_insert(collection_window_find(cd), ci);

		return TRUE;
		}

	return FALSE;
}
