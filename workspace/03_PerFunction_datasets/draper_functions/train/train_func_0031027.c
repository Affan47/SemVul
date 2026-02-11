stop_data_free (StopData *data)
{
  g_object_unref (data->simple);
  g_clear_object (&data->drive);
  g_clear_object (&data->mount_operation);

  g_free (data);
}
