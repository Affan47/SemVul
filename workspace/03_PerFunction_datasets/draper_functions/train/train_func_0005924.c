test_comment_delete (InsertCommentData *data, gconstpointer service)
{
	gboolean success;
	GError *error = NULL;

	gdata_test_mock_server_start_trace (mock_server, "comment-delete");


	success = gdata_commentable_delete_comment (GDATA_COMMENTABLE (data->parent.video), GDATA_SERVICE (service), GDATA_COMMENT (data->comment),
	                                            NULL, &error);
	g_assert_error (error, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_FORBIDDEN);
	g_assert (success == FALSE);
	g_clear_error (&error);

	gdata_mock_server_end_trace (mock_server);
}
