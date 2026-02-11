test_authorizer_refresh_authorization_async_success_no_error_cb (GDataAuthorizer *authorizer, GAsyncResult *async_result, GMainLoop *main_loop)
{
	gboolean success;
	GError *error = NULL;

	success = gdata_authorizer_refresh_authorization_finish (authorizer, async_result, &error);
	g_assert_no_error (error);
	g_assert (success == TRUE);
	g_clear_error (&error);

	g_main_loop_quit (main_loop);
}
