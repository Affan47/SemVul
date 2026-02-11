activation_find_entry (BusActivation *activation,
                       const char    *service_name,
                       DBusError     *error)
{
  BusActivationEntry *entry;

  entry = _dbus_hash_table_lookup_string (activation->entries, service_name);
  if (!entry)
    {
      if (!update_service_cache (activation, error))
        return NULL;

      entry = _dbus_hash_table_lookup_string (activation->entries,
                                              service_name);
    }
  else
    {
      BusActivationEntry *updated_entry;

      if (!check_service_file (activation, entry, &updated_entry, error))
        return NULL;

      entry = updated_entry;
    }

  if (!entry)
    {
      dbus_set_error (error, DBUS_ERROR_SERVICE_UNKNOWN,
                      "The name %s was not provided by any .service files",
                      service_name);
      return NULL;
    }

  return entry;
}
