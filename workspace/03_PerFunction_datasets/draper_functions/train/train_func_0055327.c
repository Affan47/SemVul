soup_request_default_send_async (SoupRequest          *request,
				 GCancellable         *cancellable,
				 GAsyncReadyCallback   callback,
				 gpointer              user_data)
{
	GTask *task;
	GInputStream *stream;
	GError *error = NULL;

	task = g_task_new (request, cancellable, callback, user_data);

	stream = soup_request_send (request, cancellable, &error);
	if (stream)
		g_task_return_pointer (task, stream, g_object_unref);
	else
		g_task_return_error (task, error);
	g_object_unref (task);
}
