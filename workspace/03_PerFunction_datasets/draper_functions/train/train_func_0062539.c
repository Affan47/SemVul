impl_register_keystroke_listener (DBusConnection *bus,
				  DBusMessage *message,
				  void *user_data)
{
  SpiDEController *controller = SPI_DEVICE_EVENT_CONTROLLER(user_data);
  DEControllerKeyListener *dec_listener;
  DBusMessageIter iter, iter_array;
  const char *path;
  GSList *keys = NULL;
  dbus_int32_t mask, type;
  Accessibility_EventListenerMode *mode;
 dbus_bool_t ret;
  DBusMessage *reply = NULL;
  char *keystring;

  if (strcmp (dbus_message_get_signature (message), "oa(iisi)uu(bbb)") != 0)
    return invalid_arguments_error (message);

  dbus_message_iter_init(message, &iter);
  dbus_message_iter_get_basic(&iter, &path);
  dbus_message_iter_next(&iter);
  dbus_message_iter_recurse(&iter, &iter_array);
  while (dbus_message_iter_get_arg_type(&iter_array) != DBUS_TYPE_INVALID)
  {
    Accessibility_KeyDefinition *kd = (Accessibility_KeyDefinition *)g_malloc(sizeof(Accessibility_KeyDefinition));
    if (!spi_dbus_message_iter_get_struct(&iter_array, DBUS_TYPE_INT32, &kd->keycode, DBUS_TYPE_INT32, &kd->keysym, DBUS_TYPE_STRING, &keystring, DBUS_TYPE_INVALID))
    {
      break;
    }
    kd->keystring = g_strdup (keystring);
    keys = g_slist_append(keys, kd);
  }
  dbus_message_iter_next(&iter);
  dbus_message_iter_get_basic(&iter, &mask);
  dbus_message_iter_next(&iter);
  dbus_message_iter_get_basic(&iter, &type);
  dbus_message_iter_next(&iter);
  mode = (Accessibility_EventListenerMode *)g_malloc(sizeof(Accessibility_EventListenerMode));
  if (mode)
  {
    spi_dbus_message_iter_get_struct(&iter, DBUS_TYPE_BOOLEAN, &mode->synchronous, DBUS_TYPE_BOOLEAN, &mode->preemptive, DBUS_TYPE_BOOLEAN, &mode->global, DBUS_TYPE_INVALID);
  }
#ifdef SPI_DEBUG
  fprintf (stderr, "registering keystroke listener %s:%s with maskVal %lu\n",
	   dbus_message_get_sender(message), path, (unsigned long) mask);
#endif
  dec_listener = spi_dec_key_listener_new (dbus_message_get_sender(message), path, keys, mask, type, mode);
  g_free (mode);
  ret = spi_controller_register_device_listener (
	  controller, (DEControllerListener *) dec_listener);
  reply = dbus_message_new_method_return (message);
  if (reply)
  {
    dbus_message_append_args (reply, DBUS_TYPE_BOOLEAN, &ret, DBUS_TYPE_INVALID);
  }
  return reply;
}
