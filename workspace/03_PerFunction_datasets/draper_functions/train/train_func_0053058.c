e_dbus_callback_call(E_DBus_Callback *cb, void *data, DBusError *error)
{
  if (cb && cb->cb_func)
    cb->cb_func(cb->user_data, data, error);
}
