_clutter_input_device_set_n_keys (ClutterInputDevice *device,
                                  guint               n_keys)
{
  if (device->keys != NULL)
    g_array_free (device->keys, TRUE);

  device->n_keys = n_keys;
  device->keys = g_array_sized_new (FALSE, TRUE,
                                    sizeof (ClutterKeyInfo),
                                    n_keys);
}
