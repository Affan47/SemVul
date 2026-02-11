present_channel_cb (TpChannelDispatcher *cd,
    const GError *error,
    gpointer user_data,
    GObject *weak_object)
{
  GSimpleAsyncResult *result = user_data;

  if (error != NULL)
    {
      g_simple_async_result_set_from_error (result, error);
    }

  g_simple_async_result_complete_in_idle (result);
}
