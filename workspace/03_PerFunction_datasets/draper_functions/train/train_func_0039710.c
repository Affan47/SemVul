conf_set(struct cdbus_method_call * call_ptr)
{
  const char * key;
  const char * value;
  struct pair * pair_ptr;
  char * buffer;
  bool store;

  if (!dbus_message_get_args(
        call_ptr->message,
        &cdbus_g_dbus_error,
        DBUS_TYPE_STRING, &key,
        DBUS_TYPE_STRING, &value,
        DBUS_TYPE_INVALID))
  {
    cdbus_error(call_ptr, DBUS_ERROR_INVALID_ARGS, "Invalid arguments to method \"%s\": %s",  call_ptr->method_name, cdbus_g_dbus_error.message);
    dbus_error_free(&cdbus_g_dbus_error);
    return;
  }

  log_info("set '%s' <- '%s'", key, value);

  pair_ptr = find_pair(key);
  if (pair_ptr == NULL)
  {
    pair_ptr = create_pair(key, value);
    if (pair_ptr == NULL)
    {
      cdbus_error(call_ptr, DBUS_ERROR_FAILED, "Memory allocation failed");
      return;
    }

    emit_changed(pair_ptr);

    store = true;
  }
  else
  {
    store = strcmp(pair_ptr->value, value) != 0;
    if (store)
    {
      buffer = strdup(value);
      if (buffer == NULL)
      {
        cdbus_error(call_ptr, DBUS_ERROR_FAILED, "Memory allocation failed. strdup(\"%s\") failed for value", value);
        return;
      }
      free(pair_ptr->value);
      pair_ptr->value = buffer;
      pair_ptr->version++;
      pair_ptr->stored = false;

      emit_changed(pair_ptr);
    }
    else if (!pair_ptr->stored)
    {
      store = true;
    }
  }

  if (store)
  {
    if (!store_pair(pair_ptr))
    {
      cdbus_error(call_ptr, DBUS_ERROR_FAILED, "Storing the value of key '%s' to disk failed", pair_ptr->key);
      return;
    }
  }

  cdbus_method_return_new_single(call_ptr, DBUS_TYPE_UINT64, &pair_ptr->version);
}
