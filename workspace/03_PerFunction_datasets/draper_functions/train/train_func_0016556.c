_dbus_watch_set_handler (DBusWatch        *watch,
                         DBusWatchHandler  handler,
                         void             *data,
                         DBusFreeFunction  free_data_function)
{
  if (watch->free_handler_data_function)
    (* watch->free_handler_data_function) (watch->handler_data);

  watch->handler = handler;
  watch->handler_data = data;
  watch->free_handler_data_function = free_data_function;
}
