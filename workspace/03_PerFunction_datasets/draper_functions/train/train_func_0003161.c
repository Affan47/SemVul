get_studio_list_callback(void * call_ptr, void * context, const char * studio, uint32_t modtime)
{
  DBusMessageIter struct_iter;
  DBusMessageIter dict_iter;
  bool ret;

  ret = false;

  if (!dbus_message_iter_open_container(array_iter_ptr, DBUS_TYPE_STRUCT, NULL, &struct_iter))
    goto exit;

  if (!dbus_message_iter_append_basic(&struct_iter, DBUS_TYPE_STRING, &studio))
    goto close_struct;

  if (!dbus_message_iter_open_container(&struct_iter, DBUS_TYPE_ARRAY, "{sv}", &dict_iter))
    goto close_struct;


  if (!cdbus_add_dict_entry_uint32(&dict_iter, "Modification Time", modtime))
    goto close_dict;

  ret = true;

close_dict:
  if (!dbus_message_iter_close_container(&struct_iter, &dict_iter))
    ret = false;

close_struct:
  if (!dbus_message_iter_close_container(array_iter_ptr, &struct_iter))
    ret = false;

exit:
  return ret;
}
