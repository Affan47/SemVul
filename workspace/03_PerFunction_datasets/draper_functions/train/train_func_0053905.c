handle_drive_stop (GVfsRemoteVolumeMonitor *object,
                   GDBusMethodInvocation *invocation,
                   const gchar *arg_id,
                   const gchar *arg_cancellation_id,
                   guint arg_unmount_flags,
                   const gchar *arg_mount_op_id,
                   gpointer user_data)
{
  const char *sender;
  GMountOperation *mount_operation;
  GCancellable *cancellable;
  GList *drives, *l;
  GDrive *drive;

  print_debug ("in handle_drive_stop");

  sender = g_dbus_method_invocation_get_sender (invocation);

  drive = NULL;
  drives = g_volume_monitor_get_connected_drives (monitor);
  for (l = drives; l != NULL; l = l->next)
    {
      char *drive_id;

      drive = G_DRIVE (l->data);
      drive_id = g_strdup_printf ("%p", drive);
      if (strcmp (drive_id, arg_id) == 0)
        break;

      g_free (drive_id);
    }
  if (l == NULL)
    drive = NULL;

  if (drive == NULL)
    {
      g_dbus_method_invocation_return_dbus_error (invocation,
                                                  "org.gtk.Private.RemoteVolumeMonitor.NotFound",
                                                  "The given drive was not found");
      goto out;
    }

  if (g_object_get_data (G_OBJECT (drive), "cancellable") != NULL)
    {
      g_dbus_method_invocation_return_dbus_error (invocation,
                                                  "org.gtk.Private.RemoteVolumeMonitor.Failed",
                                                  "An operation is already pending");
      goto out;
    }

  cancellable = g_cancellable_new ();
  g_object_set_data_full (G_OBJECT (drive), "cancellable", cancellable, g_object_unref);
  g_object_set_data_full (G_OBJECT (cancellable), "owner", g_strdup (sender), g_free);
  g_object_set_data_full (G_OBJECT (cancellable), "cancellation_id", g_strdup (arg_cancellation_id), g_free);
  outstanding_ops = g_list_prepend (outstanding_ops, cancellable);
  g_object_weak_ref (G_OBJECT (cancellable),
                     cancellable_destroyed_cb,
                     NULL);

  mount_operation = NULL;
  if (arg_mount_op_id != NULL && strlen (arg_mount_op_id) > 0)
    {
      mount_operation = wrap_mount_op (arg_mount_op_id, sender, object);
      g_object_set_data_full (G_OBJECT (drive), "mount_operation", mount_operation, g_object_unref);
    }

  g_drive_stop (drive,
                arg_unmount_flags,
                mount_operation,
                cancellable,
                (GAsyncReadyCallback) drive_stop_cb,
                g_object_ref (invocation));

 out:
  if (drives != NULL)
    g_list_free_full (drives, g_object_unref);
  return TRUE;
}
