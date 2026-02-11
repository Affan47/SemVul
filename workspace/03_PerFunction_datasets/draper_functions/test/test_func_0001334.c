bus_activation_set_environment_variable (BusActivation     *activation,
                                         const char        *key,
                                         const char        *value,
                                         DBusError         *error)
{
  char        *hash_key;
  char        *hash_value;
  dbus_bool_t  retval;

  retval = FALSE;
  hash_key = NULL;
  hash_value = NULL;
  hash_key = _dbus_strdup (key);

  if (hash_key == NULL)
    goto out;

  hash_value = _dbus_strdup (value);

  if (hash_value == NULL)
    goto out;

  if (!_dbus_hash_table_insert_string (activation->environment,
                                       hash_key, hash_value))
    goto out;

  retval = TRUE;
out:
  if (retval == FALSE)
    {
      dbus_free (hash_key);
      dbus_free (hash_value);
      BUS_SET_OOM (error);
    }

  return retval;
}
