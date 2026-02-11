_dbus_timeout_list_toggle_timeout (DBusTimeoutList           *timeout_list,
                                   DBusTimeout               *timeout,
                                   dbus_bool_t                enabled)
{
  enabled = !!enabled;

  if (enabled == timeout->enabled)
    return;

  timeout->enabled = enabled;

  if (timeout_list->timeout_toggled_function != NULL)
    (* timeout_list->timeout_toggled_function) (timeout,
                                                timeout_list->timeout_data);
}
