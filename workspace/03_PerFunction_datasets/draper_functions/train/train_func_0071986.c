meta_compare_func(meta_thread_data *mt1, meta_thread_data *mt2)
{
	if((mt1->type&META_QUERY_DATA_TYPES) != (mt2->type&META_QUERY_DATA_TYPES))
		return TRUE;
	if(!gmpc_meta_watcher_match_data(mt1->type&META_QUERY_DATA_TYPES, mt1->song, mt2->song))
	{
		return TRUE;
	}
	return FALSE;
}
