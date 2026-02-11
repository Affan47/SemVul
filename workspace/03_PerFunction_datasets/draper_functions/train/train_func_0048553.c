_dbus_tracker_steroids_query (TrackerSteroids* self, GVariant* parameters, GDBusMethodInvocation* invocation) {
	GVariantIter _arguments_iter;
	gint _fd_index = 0;
	gchar* query = NULL;
	GVariant* _tmp7_;
	GUnixOutputStream* output_stream = NULL;
	g_variant_iter_init (&_arguments_iter, parameters);
	_tmp7_ = g_variant_iter_next_value (&_arguments_iter);
	query = g_variant_dup_string (_tmp7_, NULL);
	g_variant_unref (_tmp7_);
	g_variant_iter_next (&_arguments_iter, "h", &_fd_index);
	output_stream = (GUnixOutputStream *) g_unix_output_stream_new (g_unix_fd_list_get (g_dbus_message_get_unix_fd_list (g_dbus_method_invocation_get_message (invocation)), _fd_index, NULL), TRUE);
	tracker_steroids_query (self, g_dbus_method_invocation_get_sender (invocation), query, output_stream, (GAsyncReadyCallback) _dbus_tracker_steroids_query_ready, invocation);
	_g_free0 (query);
	_g_object_unref0 (output_stream);
}
