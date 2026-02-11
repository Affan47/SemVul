image_get_collection(ImageWindow *imd, CollectInfo **info)
{
	if (collection_to_number(imd->collection) >= 0)
		{
		if (g_list_find(imd->collection->list, imd->collection_info) != NULL)
			{
			if (info) *info = imd->collection_info;
			}
		else
			{
			if (info) *info = NULL;
			}
		return imd->collection;
		}

	if (info) *info = NULL;
	return NULL;
}
