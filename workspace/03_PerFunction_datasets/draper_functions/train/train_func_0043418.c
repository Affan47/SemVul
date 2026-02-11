tracker_extract_get_metadata (TrackerExtractInfo *info)
{
	TotemPlParser *pl;
	TrackerSparqlBuilder *metadata;
	PlaylistMetadata data;
	GFile *file;
	gchar *uri;

	pl = totem_pl_parser_new ();
	file = tracker_extract_info_get_file (info);
	uri = g_file_get_uri (file);
	metadata = tracker_extract_info_get_metadata_builder (info);

	data.track_counter = PLAYLIST_DEFAULT_NO_TRACKS;
	data.total_time =  PLAYLIST_DEFAULT_DURATION;
	data.title = NULL;
	data.metadata = metadata;

	g_object_set (pl, "recurse", FALSE, "disable-unsafe", TRUE, NULL);

	g_signal_connect (G_OBJECT (pl), "playlist-started", G_CALLBACK (playlist_started), &data);
	g_signal_connect (G_OBJECT (pl), "entry-parsed", G_CALLBACK (entry_parsed), &data);

	tracker_sparql_builder_predicate (metadata, "a");
	tracker_sparql_builder_object (metadata, "nmm:Playlist");
	tracker_sparql_builder_object (metadata, "nfo:MediaList");

	if (totem_pl_parser_parse (pl, uri, FALSE) == TOTEM_PL_PARSER_RESULT_SUCCESS) {
		if (data.title != NULL) {
			g_message ("Playlist title:'%s'", data.title);
			tracker_sparql_builder_predicate (metadata, "nie:title");
			tracker_sparql_builder_object_unvalidated (metadata, data.title);
			g_free (data.title);
		} else {
			g_message ("Playlist has no title");
		}

		if (data.total_time > 0) {
			tracker_sparql_builder_predicate (metadata, "nfo:listDuration");
			tracker_sparql_builder_object_int64 (metadata, data.total_time);
		}

		if (data.track_counter > 0) {
			tracker_sparql_builder_predicate (metadata, "nfo:entryCounter");
			tracker_sparql_builder_object_int64 (metadata, data.track_counter);
		}
	} else {
		g_warning ("Playlist could not be parsed, no error given");
	}

	g_object_unref (pl);
	g_free (uri);

	return TRUE;
}
