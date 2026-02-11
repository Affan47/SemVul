handle_cancel_operation (GVfsRemoteVolumeMonitor *object,
                         GDBusMethodInvocation *invocation,
                         const gchar *arg_cancellation_id,
                         gpointer user_data)
{
  gboolean was_cancelled;
  const char *sender;
  GList *l;

  was_cancelled = FALSE;

  sender = g_dbus_method_invocation_get_sender (invocation);

  print_debug ("in handle_cancel_operation");


  for (l = outstanding_ops; l != NULL; l = l->next)
    {
      GCancellable *cancellable = G_CANCELLABLE (l->data);
      const gchar *owner;
      const gchar *id;

      owner = g_object_get_data (G_OBJECT (cancellable), "owner");
      id = g_object_get_data (G_OBJECT (cancellable), "cancellation_id");
      if (g_strcmp0 (owner, sender) == 0 && g_strcmp0 (id, arg_cancellation_id) == 0)
        {
          print_debug ("found op to cancel");
          g_cancellable_cancel (cancellable);

          was_cancelled = TRUE;
          break;
        }
    }

  if (!was_cancelled)
    g_warning ("didn't find op to cancel");

  gvfs_remote_volume_monitor_complete_cancel_operation (object, invocation, was_cancelled);

  return TRUE;
}
