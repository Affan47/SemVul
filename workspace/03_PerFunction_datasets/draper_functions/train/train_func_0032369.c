collection_table_motion_update(CollectTable *ct, gint x, gint y, gboolean drop_event)
{
	CollectInfo *info;

	info = collection_table_find_data_by_coord(ct, x, y, NULL);

	if (drop_event)
		{
		tip_unschedule(ct);
		collection_table_insert_marker(ct, info, TRUE);
		}
	else
		{
		tip_update(ct, info);
		}
}
