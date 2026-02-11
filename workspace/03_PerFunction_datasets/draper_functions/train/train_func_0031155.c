audiocd_info_thread (GSimpleAsyncResult *result, GObject *object, GCancellable *cancellable)
{
	RBAudioCDInfo *info;
	GError *error = NULL;

	info = g_simple_async_result_get_op_res_gpointer (result);

	if (read_gst_disc_info (info, &error)) {
		read_gvfs_disc_info (info);
	} else {
		rb_audiocd_info_free (info);
		g_simple_async_result_set_op_res_gpointer (result, NULL, NULL);
		g_simple_async_result_take_error (result, error);
	}
}
