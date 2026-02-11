bus_activation_unref (BusActivation *activation)
{
  _dbus_assert (activation->refcount > 0);

  activation->refcount -= 1;

  if (activation->refcount > 0)
    return;

  dbus_free (activation->server_address);
  if (activation->entries)
    _dbus_hash_table_unref (activation->entries);
  if (activation->pending_activations)
    _dbus_hash_table_unref (activation->pending_activations);
  if (activation->directories)
    _dbus_hash_table_unref (activation->directories);
  if (activation->environment)
    _dbus_hash_table_unref (activation->environment);

  dbus_free (activation);
}
