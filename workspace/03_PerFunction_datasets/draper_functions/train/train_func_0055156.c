handle_set_bitmap_location (UDisksMDRaid           *_mdraid,
                            GDBusMethodInvocation  *invocation,
                            const gchar            *value,
                            GVariant               *options)
{
  UDisksLinuxMDRaid *mdraid = UDISKS_LINUX_MDRAID (_mdraid);
  UDisksDaemon *daemon;
  UDisksState *state;
  UDisksLinuxMDRaidObject *object;
  const gchar *action_id;
  const gchar *message;
  uid_t started_by_uid;
  uid_t caller_uid;
  gid_t caller_gid;
  UDisksLinuxDevice *raid_device = NULL;
  const gchar *device_file = NULL;
  gchar *escaped_device_file = NULL;
  GError *error = NULL;
  gchar *error_message = NULL;

  object = udisks_daemon_util_dup_object (mdraid, &error);
  if (object == NULL)
    {
      g_dbus_method_invocation_take_error (invocation, error);
      goto out;
    }

  daemon = udisks_linux_mdraid_object_get_daemon (object);
  state = udisks_daemon_get_state (daemon);

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

  if (!(g_strcmp0 (value, "none") == 0 || g_strcmp0 (value, "internal") == 0))
    {
      g_dbus_method_invocation_return_error (invocation, UDISKS_ERROR, UDISKS_ERROR_FAILED,
                                             "Only values 'none' and 'internal' are currently supported.");
      goto out;
    }

  raid_device = udisks_linux_mdraid_object_get_device (object);
  if (raid_device == NULL)
    {
      g_dbus_method_invocation_return_error (invocation, UDISKS_ERROR, UDISKS_ERROR_FAILED,
                                             "RAID Array is not running");
      goto out;
    }

  if (!udisks_state_has_mdraid (state,
                                g_udev_device_get_device_number (raid_device->udev_device),
                                &started_by_uid))
    {

      started_by_uid = 0;
    }


  if (caller_uid != 0 && (caller_uid != started_by_uid))
    {


      message = N_("Authentication is required to configure the write-intent bitmap on a RAID array");
      action_id = "org.freedesktop.udisks2.manage-md-raid";
      if (!udisks_daemon_util_check_authorization_sync (daemon,
                                                        UDISKS_OBJECT (object),
                                                        action_id,
                                                        options,
                                                        message,
                                                        invocation))
        goto out;
    }

  device_file = g_udev_device_get_device_file (raid_device->udev_device);
  escaped_device_file = udisks_daemon_util_escape_and_quote (device_file);

  if (!udisks_daemon_launch_spawned_job_sync (daemon,
                                              UDISKS_OBJECT (object),
                                              "md-raid-set-bitmap", caller_uid,
                                              NULL,
                                              0,
                                              0,
                                              NULL,
                                              &error_message,
                                              NULL,
                                              "mdadm --grow %s --bitmap %s",
                                              escaped_device_file,
                                              value))
    {
      g_dbus_method_invocation_return_error (invocation,
                                             UDISKS_ERROR,
                                             UDISKS_ERROR_FAILED,
                                             "Error setting bitmap on RAID array %s: %s",
                                             device_file,
                                             error_message);
      goto out;
    }

  udisks_mdraid_complete_add_device (_mdraid, invocation);

 out:
  g_free (error_message);
  g_free (escaped_device_file);
  g_clear_object (&raid_device);
  g_clear_object (&object);
  return TRUE;
}
