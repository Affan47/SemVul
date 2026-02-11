get_original_date_for_test (GthTest        *test,
			    GthFileData    *file_data,
			    gconstpointer  *data,
			    GDestroyNotify *data_destroy_func)
{
	GthDateTime *datetime;
	GthMetadata *metadata;

	datetime = gth_datetime_new ();
	metadata = (GthMetadata *) g_file_info_get_attribute_object (file_data->info, "Embedded::Photo::DateTimeOriginal");
	if (metadata != NULL)
		gth_datetime_from_exif_date (datetime, gth_metadata_get_raw (metadata));

	*data = g_date_new ();
	*((GDate *)*data) = *datetime->date;
	*data_destroy_func = (GDestroyNotify) g_date_free;

	gth_datetime_free (datetime);

	return 0;
}
