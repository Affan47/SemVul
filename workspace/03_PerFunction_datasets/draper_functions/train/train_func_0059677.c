on_notify_view_window (UnityWebappsGenContext *context,
			  gint interest_id,
		       guint64 window,
			  gpointer user_data)
{
  unity_webapps_context_notify_data *data;

  data = (unity_webapps_context_notify_data *)user_data;
  g_return_if_fail (data != NULL);
  g_return_if_fail (data->context != NULL);

  if (!G_IS_OBJECT (data->context))
    return;

  if (data->window_callback != NULL)
    data->window_callback(data->context, interest_id, window, data->user_data);
}
