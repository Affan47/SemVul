mountable_mount (VfsMountable *mountable,
		 GMountSpec *mount_spec,
		 GMountSource *source,
		 gboolean automount,
		 MountCallback callback,
		 gpointer user_data)
{
  MountData *data;

  data = g_new0 (MountData, 1);
  data->automount = automount;
  data->mountable = mountable;
  data->source = g_object_ref (source);
  data->mount_spec = g_mount_spec_ref (mount_spec);
  data->callback = callback;
  data->user_data = user_data;

  if (mountable->dbus_name == NULL)
    spawn_mount (data);
  else
    mountable_mount_with_name (data, mountable->dbus_name);
}
