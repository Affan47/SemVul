_dbus_register_shutdown_func (DBusShutdownFunction  func,
                              void                 *data)
{
  ShutdownClosure *c;

  c = dbus_new (ShutdownClosure, 1);

  if (c == NULL)
    return FALSE;

  c->func = func;
  c->data = data;

  _DBUS_LOCK (shutdown_funcs);

  c->next = registered_globals;
  registered_globals = c;

  _DBUS_UNLOCK (shutdown_funcs);

  return TRUE;
}
