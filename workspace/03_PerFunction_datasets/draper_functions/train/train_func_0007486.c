lash_server_register_client(struct cdbus_method_call * call_ptr)
{
  const char * sender;
  const char * class;
  dbus_uint64_t pid;
  dbus_uint32_t flags;
  ladish_app_handle app;

  if (!dbus_message_get_args(
        call_ptr->message,
        &cdbus_g_dbus_error,
        DBUS_TYPE_UINT64, &pid,
        DBUS_TYPE_STRING, &class,
        DBUS_TYPE_UINT32, &flags,
        DBUS_TYPE_INVALID))
  {
    cdbus_error(call_ptr, DBUS_ERROR_INVALID_ARGS, "Invalid arguments to method \"%s\": %s",  call_ptr->method_name, cdbus_g_dbus_error.message);
    dbus_error_free(&cdbus_g_dbus_error);
    return;
  }

  sender = dbus_message_get_sender(call_ptr->message);

  log_info("LASH client registered. pid=%"PRIu64" dbusname='%s' class='%s' flags=0x%"PRIu32")", pid, sender, class, flags);

  app = ladish_find_app_by_pid((pid_t)pid, NULL);
  if (app == NULL)
  {
    log_error("Unknown LASH app registered");
    return;
  }

  ladish_app_set_dbus_name(app, sender);
  ladish_app_restore(app);
}
