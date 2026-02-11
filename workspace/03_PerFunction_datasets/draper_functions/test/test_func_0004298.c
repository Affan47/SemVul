notify_keystroke_listener (SpiDEController *controller,
                           DEControllerKeyListener *listener,
                           gboolean enable)
{
  const char *path = SPI_DBUS_PATH_DEC;
  const char *interface = SPI_DBUS_INTERFACE_DEVICE_EVENT_LISTENER;
  const char *name = (enable
                      ? "KeystrokeListenerRegistered"
                      : "KeystrokeListenerDeregistered");
  DBusMessage *signal;
  DBusMessageIter iter;

  signal = dbus_message_new_signal (path, interface, name);
  if (!signal)
    return;
  dbus_message_iter_init_append (signal, &iter);
  append_keystroke_listener (&iter, listener);
  dbus_connection_send (controller->bus, signal, NULL);
  dbus_message_unref (signal);
}
