ladish_new_studio(struct cdbus_method_call * call_ptr)
{
  const char * name;

  dbus_error_init(&cdbus_g_dbus_error);

  if (!dbus_message_get_args(call_ptr->message, &cdbus_g_dbus_error, DBUS_TYPE_STRING, &name, DBUS_TYPE_INVALID))
  {
    cdbus_error(call_ptr, DBUS_ERROR_INVALID_ARGS, "Invalid arguments to method \"%s\": %s",  call_ptr->method_name, cdbus_g_dbus_error.message);
    dbus_error_free(&cdbus_g_dbus_error);
    return;
  }

  log_info("New studio request (%s)", name);

  if (ladish_command_new_studio(call_ptr, ladish_studio_get_cmd_queue(), name))
  {
    cdbus_method_return_new_void(call_ptr);
  }
}
