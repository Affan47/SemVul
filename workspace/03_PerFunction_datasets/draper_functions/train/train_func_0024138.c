mismatched_stats_foreach_func (gpointer key, gpointer value, gpointer user_data)
{
	MismatchedFilesStats *stats = (MismatchedFilesStats*)value;
	StringLocation *location;
	MonoProfiler *prof = (MonoProfiler*)user_data;
	guint32 hash;
	gboolean bannerShown = FALSE;

	hash = do_calc_string_hash (0, stats->requestedName);
	fprintf (stdout,
		 "    Count: %u\n"
		 "Requested: %s\n"
		 "   Actual: %s\n",
		 stats->count, stats->requestedName, stats->actualName);

	if (!prof->may_have_locations) {
		fprintf (stdout, "\n");
		return;
	}

	location = (StringLocation *)g_hash_table_lookup (prof->string_locations_hash, &hash);
	while (location) {
		if (location->hint && strlen (location->hint) > 0) {
			if (!bannerShown) {
				fprintf (stdout, "Locations:\n");
				bannerShown = TRUE;
			}
			fprintf (stdout, "%s", location->hint);
		}
		location = location->next;
		if (location)
			fprintf (stdout, LOCATION_INDENT "--\n");
	}

	fprintf (stdout, "\n");
}
