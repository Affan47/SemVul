presence_changed_notify (GObject *object,
			 GParamSpec *pspec,
			 gpointer user_data)
{
  unity_webapps_indicator_action_data *data;

  data = (unity_webapps_indicator_action_data *)user_data;
  g_return_if_fail(data != NULL);

  if (!G_IS_OBJECT(data->context))
    return;

  if (data->callback != NULL)
    data->callback (data->context, data->user_data);
}
