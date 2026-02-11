add_dispatch_operation_cb (TpSimpleApprover *self,
    TpAccount *account,
    TpConnection *connection,
    GList *channels,
    TpChannelDispatchOperation *cdo,
    TpAddDispatchOperationContext *context,
    gpointer user_data)
{
  GList *l;
  GStrv possible_handlers;
  gchar c;

  g_print ("Approving this batch of channels:\n");

  g_signal_connect (cdo, "invalidated", G_CALLBACK (cdo_finished_cb), NULL);

  for (l = channels; l != NULL; l = g_list_next (l))
    {
      TpChannel *channel = l->data;

      g_print ("%s channel with %s\n", tp_channel_get_channel_type (channel),
          tp_channel_get_identifier (channel));
    }

  possible_handlers = tp_channel_dispatch_operation_get_possible_handlers (
      cdo);
  if (possible_handlers[0] == NULL)
    {
      g_print ("\nNo possible handler suggested\n");
    }
  else
    {
      guint i;

      g_print ("\npossible handlers:\n");
      for (i = 0; possible_handlers[i] != NULL; i++)
        g_print ("  %s\n", possible_handlers[i]);
    }

  g_object_ref (cdo);

  tp_add_dispatch_operation_context_accept (context);

  g_print ("Approve? [y/n]\n");

  c = fgetc (stdin);

  if (c == 'y' || c == 'Y')
    {
      g_print ("Approve channels\n");

      tp_channel_dispatch_operation_handle_with_async (cdo, NULL,
          handle_with_cb, NULL);
    }
  else if (c == 'n' || c == 'N')
    {
      g_print ("Reject channels\n");

      tp_channel_dispatch_operation_close_channels_async (cdo, close_cb, NULL);
    }
  else
    {
      g_print ("Ignore channels\n");
    }
}
