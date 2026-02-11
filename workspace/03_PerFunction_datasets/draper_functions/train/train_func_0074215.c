tracker_extract_get_metadata (TrackerExtractInfo *info)
{
	TrackerSparqlBuilder *metadata;
	guint max_width;
	guint max_height;
	GFile *file;
	gchar *uri;

	metadata = tracker_extract_info_get_metadata_builder (info);
	file = tracker_extract_info_get_file (info);
	uri = g_file_get_uri (file);


	tracker_sparql_builder_predicate (metadata, "a");
	tracker_sparql_builder_object (metadata, "nfo:Image");
	tracker_sparql_builder_object (metadata, "nfo:Icon");

	if (find_max_width_and_height (uri, &max_width, &max_height)) {
		if (max_width > 0) {
			tracker_sparql_builder_predicate (metadata, "nfo:width");
			tracker_sparql_builder_object_int64 (metadata, (gint64) max_width);
		}
		if (max_height > 0) {
			tracker_sparql_builder_predicate (metadata, "nfo:height");
			tracker_sparql_builder_object_int64 (metadata, (gint64) max_height);
		}
	}

	g_free (uri);

	return TRUE;
}
