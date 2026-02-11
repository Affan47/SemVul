mount_data_free (MountData *data)
{
  g_object_unref (data->source);
  g_mount_spec_unref (data->mount_spec);
  g_free (data->obj_path);
  g_clear_object (&data->spawner);

  g_free (data);
}
