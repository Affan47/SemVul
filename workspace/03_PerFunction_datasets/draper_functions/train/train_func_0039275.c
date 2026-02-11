handle_channels (TpSimpleHandler *handler,
    TpAccount *account,
    TpConnection *conn,
    GList *channels,
    GList *requests,
    gint64 action_time,
    TpHandleChannelsContext *context,
    gpointer user_data)
{
  TpDBusTubeChannel *tube;
  GList *l;
  GError error = { TP_ERROR, TP_ERROR_NOT_AVAILABLE,
      "No channel to be handled" };

  g_message ("Handling channels");

  for (l = channels; l != NULL; l = l->next)
    {
      TpDBusTubeChannel *channel = l->data;

      if (!TP_IS_DBUS_TUBE_CHANNEL (channel))
        continue;

      if (tp_strdiff (tp_dbus_tube_channel_get_service_name (channel),
            EXAMPLE_SERVICE_NAME))
        continue;

      g_message ("Accepting tube");

      tube = g_object_ref (channel);

      g_signal_connect (tube, "invalidated",
          G_CALLBACK (tube_invalidated_cb), NULL);

      tp_dbus_tube_channel_accept_async (tube, tube_accepted, context);

      tp_handle_channels_context_accept (context);
      return;
    }

  g_message ("Rejecting channels");
  tp_handle_channels_context_fail (context, &error);
}
