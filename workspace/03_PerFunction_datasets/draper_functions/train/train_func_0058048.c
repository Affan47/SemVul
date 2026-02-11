brasero_project_get_sectors_string (gint64 sectors,
				    BraseroTrackType *type)
{
	gint64 size_bytes;

	if (brasero_track_type_get_has_stream (type)) {
		if (BRASERO_STREAM_FORMAT_HAS_VIDEO (brasero_track_type_get_stream_format (type)))


			size_bytes = sectors * 2048LL * 72000LL / 47LL;
		else
			size_bytes = sectors * GST_SECOND / 75LL;
		return brasero_units_get_time_string (size_bytes, TRUE, FALSE);
	}
	else {
		size_bytes = sectors * 2048LL;
		return g_format_size (size_bytes);
	}
}
