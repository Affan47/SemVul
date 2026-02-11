dbus_server_set_watch_functions (DBusServer              *server,
                                 DBusAddWatchFunction     add_function,
                                 DBusRemoveWatchFunction  remove_function,
                                 DBusWatchToggledFunction toggled_function,
                                 void                    *data,
                                 DBusFreeFunction         free_data_function)
{
  dbus_bool_t result;
  DBusWatchList *watches;

  _dbus_return_val_if_fail (server != NULL, FALSE);

  SERVER_LOCK (server);
  watches = server->watches;
  server->watches = NULL;
  if (watches)
    {
      SERVER_UNLOCK (server);
      result = _dbus_watch_list_set_functions (watches,
                                               add_function,
                                               remove_function,
                                               toggled_function,
                                               data,
                                               free_data_function);
      SERVER_LOCK (server);
    }
  else
    {
      _dbus_warn_check_failed ("Re-entrant call to %s\n", _DBUS_FUNCTION_NAME);
      result = FALSE;
    }
  server->watches = watches;
  SERVER_UNLOCK (server);

  return result;
}
