impl_GetItems (DBusConnection * bus, DBusMessage * message, void *user_data)
{
  DBusMessage *reply;
  DBusMessageIter iter, iter_array;
  GSList *pending_unrefs = NULL;

  if (bus == spi_global_app_data->bus)
    spi_atk_add_client (dbus_message_get_sender (message));

  reply = dbus_message_new_method_return (message);

  dbus_message_iter_init_append (reply, &iter);
  dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
                                    SPI_CACHE_ITEM_SIGNATURE, &iter_array);
  spi_cache_foreach (spi_global_cache, ref_accessible_hf, NULL);
  spi_cache_foreach (spi_global_cache, append_accessible_hf, &iter_array);
  spi_cache_foreach (spi_global_cache, add_to_list_hf, &pending_unrefs);
  g_slist_free_full (pending_unrefs, g_object_unref);
  dbus_message_iter_close_container (&iter, &iter_array);
  return reply;
}
