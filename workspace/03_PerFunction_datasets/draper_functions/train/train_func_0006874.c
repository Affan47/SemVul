handle_delete (UDisksPartition        *partition,
               GDBusMethodInvocation  *invocation,
               GVariant               *options)
{
  const gchar *action_id = NULL;
  const gchar *message = NULL;
  UDisksBlock *block = NULL;
  UDisksObject *object = NULL;
  UDisksDaemon *daemon = NULL;
  gchar *error_message = NULL;
  gchar *escaped_device = NULL;
  UDisksObject *partition_table_object = NULL;
  UDisksPartitionTable *partition_table = NULL;
  UDisksBlock *partition_table_block = NULL;
  gchar *command_line = NULL;
  uid_t caller_uid;
  gid_t caller_gid;
  pid_t caller_pid;
  GError *error;

  error = NULL;
  object = udisks_daemon_util_dup_object (partition, &error);
  if (object == NULL)
    {
      g_dbus_method_invocation_take_error (invocation, error);
      goto out;
    }

  daemon = udisks_linux_block_object_get_daemon (UDISKS_LINUX_BLOCK_OBJECT (object));
  block = udisks_object_get_block (object);

  error = NULL;
  if (!udisks_daemon_util_get_caller_pid_sync (daemon,
                                               invocation,
                                               NULL ,
                                               &caller_pid,
                                               &error))
    {
      g_dbus_method_invocation_return_gerror (invocation, error);
      g_error_free (error);
      goto out;
    }

  error = NULL;
  if (!udisks_daemon_util_get_caller_uid_sync (daemon,
                                               invocation,
                                               NULL ,
                                               &caller_uid,
                                               &caller_gid,
                                               NULL,
                                               &error))
    {
      g_dbus_method_invocation_return_gerror (invocation, error);
      g_error_free (error);
      goto out;
    }

  partition_table_object = udisks_daemon_find_object (daemon, udisks_partition_get_table (partition));
  partition_table = udisks_object_get_partition_table (partition_table_object);
  partition_table_block = udisks_object_get_block (partition_table_object);

  action_id = "org.freedesktop.udisks2.modify-device";


  message = N_("Authentication is required to delete the partition $(drive)");
  if (!udisks_daemon_util_setup_by_user (daemon, object, caller_uid))
    {
      if (udisks_block_get_hint_system (block))
        {
          action_id = "org.freedesktop.udisks2.modify-device-system";
        }
      else if (!udisks_daemon_util_on_same_seat (daemon, object, caller_pid))
        {
          action_id = "org.freedesktop.udisks2.modify-device-other-seat";
        }
    }
  if (!udisks_daemon_util_check_authorization_sync (daemon,
                                                    object,
                                                    action_id,
                                                    options,
                                                    message,
                                                    invocation))
    goto out;

  escaped_device = udisks_daemon_util_escape_and_quote (udisks_block_get_device (partition_table_block));

  if (!udisks_daemon_launch_spawned_job_sync (daemon,
                                              partition_table_object,
                                              "partition-delete", caller_uid,
                                              NULL,
                                              0,
                                              0,
                                              NULL,
                                              &error_message,
                                              NULL,
                                              "parted --script %s \"rm %d\"",
                                              escaped_device,
                                              udisks_partition_get_number (partition)))
    {
      g_dbus_method_invocation_return_error (invocation,
                                             UDISKS_ERROR,
                                             UDISKS_ERROR_FAILED,
                                             "Error deleting partition %s: %s",
                                             udisks_block_get_device (block),
                                             error_message);
      goto out;
    }

  udisks_linux_block_object_trigger_uevent (UDISKS_LINUX_BLOCK_OBJECT (partition_table_object));

  udisks_partition_complete_delete (partition, invocation);

 out:
  g_free (command_line);
  g_free (escaped_device);
  g_free (error_message);
  g_clear_object (&object);
  g_clear_object (&block);
  g_clear_object (&partition_table_object);
  g_clear_object (&partition_table);
  g_clear_object (&partition_table_block);
  g_clear_object (&object);

  return TRUE;
}
