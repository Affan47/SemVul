add_input_mode_device   (AnnotateData    *data,
                         GdkDevice       *device,
                         GdkInputMode     mode)
{
  if (!data->devdatatable)
    {
      data->devdatatable = g_hash_table_new (NULL, NULL);
    }

  AnnotateDeviceData *devdata = (AnnotateDeviceData *) NULL;
  devdata  = g_malloc ((gsize) sizeof (AnnotateDeviceData));
  devdata->coord_list = (GSList *) NULL;
  g_hash_table_insert(data->devdatatable, device, devdata);

  if (!gdk_device_set_mode (device, mode))
    {
      g_warning ("Unable to set the device %s to the %d mode\n",
                  gdk_device_get_name (device),
                  mode);
    }

  g_printerr ("Enabled Device in screen %d. %p: \"%s\" (Type: %d)\n",
               mode,
               device,
               gdk_device_get_name (device),
               gdk_device_get_source (device));
}
