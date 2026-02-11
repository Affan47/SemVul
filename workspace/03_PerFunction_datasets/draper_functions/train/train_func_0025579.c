e_tz_map_get_location_by_name (ETzMap *tzmap, const gchar *name)
{
	TzLocation *tz_loc = NULL;
	TzDB *tz_db;
	GPtrArray *locs;
	guint i;

	tz_db = e_tz_map_get_tz_db (tzmap);
	locs = tz_get_locations (tz_db);

	for (i = 0; i < locs->len; i++)
	{
		TzLocation *tz_loc_temp;

		tz_loc_temp = g_ptr_array_index (locs, i);

		if (!strcmp (tz_location_get_zone (tz_loc_temp), name))
		{
			tz_loc = tz_loc_temp;
			break;
		}
	}

	return tz_loc;
}
