on_conf_changed(void * context, DBusMessage * message_ptr)
{
  const char * key;
  const char * value;
  dbus_uint64_t version;
  struct pair * pair_ptr;

  if (!dbus_message_get_args(
        message_ptr,
        &cdbus_g_dbus_error,
        DBUS_TYPE_STRING, &key,
        DBUS_TYPE_STRING, &value,
        DBUS_TYPE_UINT64, &version,
        DBUS_TYPE_INVALID))
  {
    log_error("Invalid parameters of \"changed\" signal: %s",  cdbus_g_dbus_error.message);
    dbus_error_free(&cdbus_g_dbus_error);
    return;
  }

  pair_ptr = find_pair(key);
  if (pair_ptr == NULL)
  {

    return;
  }

  if (pair_ptr->version >= version)
  {

    return;
  }

  if (pair_ptr->value != NULL && strcmp(value, pair_ptr->value) == 0)
  {


    return;
  }

  on_value_changed(pair_ptr, value, version, true);
}
