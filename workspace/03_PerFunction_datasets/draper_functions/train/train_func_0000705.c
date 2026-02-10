test_upload_simple (UploadData *data, gconstpointer service)
{
	GDataUploadStream *upload_stream;
	GFileInputStream *file_stream;
	const gchar * const *tags, * const *tags2;
	gssize transfer_size;
	GError *error = NULL;

	gdata_test_mock_server_start_trace (mock_server, "upload-simple");


	upload_stream = gdata_youtube_service_upload_video (GDATA_YOUTUBE_SERVICE (service), data->video, data->slug, data->content_type, NULL,
	                                                    &error);
	g_assert_no_error (error);
	g_assert (GDATA_IS_UPLOAD_STREAM (upload_stream));


	file_stream = g_file_read (data->video_file, NULL, &error);
	g_assert_no_error (error);
	g_assert (G_IS_FILE_INPUT_STREAM (file_stream));


	transfer_size = g_output_stream_splice (G_OUTPUT_STREAM (upload_stream), G_INPUT_STREAM (file_stream),
	                                        G_OUTPUT_STREAM_SPLICE_CLOSE_SOURCE | G_OUTPUT_STREAM_SPLICE_CLOSE_TARGET, NULL, &error);
	g_assert_no_error (error);
	g_assert_cmpint (transfer_size, >, 0);


	data->updated_video = gdata_youtube_service_finish_video_upload (GDATA_YOUTUBE_SERVICE (service), upload_stream, &error);
	g_assert_no_error (error);
	g_assert (GDATA_IS_YOUTUBE_VIDEO (data->updated_video));

	g_object_unref (file_stream);
	g_object_unref (upload_stream);


	g_assert (gdata_entry_is_inserted (GDATA_ENTRY (data->updated_video)));
	g_assert_cmpstr (gdata_entry_get_title (GDATA_ENTRY (data->updated_video)), ==, gdata_entry_get_title (GDATA_ENTRY (data->video)));
	g_assert_cmpstr (gdata_youtube_video_get_description (data->updated_video), ==, gdata_youtube_video_get_description (data->video));
	g_assert_cmpstr (gdata_media_category_get_category (gdata_youtube_video_get_category (data->updated_video)), ==,
	                 gdata_media_category_get_category (gdata_youtube_video_get_category (data->video)));

	tags = gdata_youtube_video_get_keywords (data->video);
	tags2 = gdata_youtube_video_get_keywords (data->updated_video);
	g_assert_cmpuint (g_strv_length ((gchar**) tags2), ==, g_strv_length ((gchar**) tags));
	g_assert_cmpstr (tags2[0], ==, tags[0]);
	g_assert_cmpstr (tags2[1], ==, tags[1]);
	g_assert_cmpstr (tags2[2], ==, tags[2]);

	gdata_mock_server_end_trace (mock_server);
}
