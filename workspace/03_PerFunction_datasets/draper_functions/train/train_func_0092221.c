bus_dbus_impl_forward_message_idle_cb (BusDBusImpl   *dbus)
{
    g_return_val_if_fail (dbus->forward_queue != NULL, FALSE);

    g_mutex_lock (&dbus->forward_lock);
    BusForwardData *data = (BusForwardData *) dbus->forward_queue->data;
    dbus->forward_queue = g_list_delete_link (dbus->forward_queue, dbus->forward_queue);
    gboolean has_message = (dbus->forward_queue != NULL);
    g_mutex_unlock (&dbus->forward_lock);

    do {
        const gchar *destination = g_dbus_message_get_destination (data->message);
        BusConnection *dest_connection = NULL;
        if (destination != NULL)
            dest_connection = bus_dbus_impl_get_connection_by_name (dbus, destination);
        if (dest_connection != NULL) {

            if (g_dbus_message_get_body (data->message) == NULL)
                g_dbus_message_set_signature (data->message, NULL);
            GError *error = NULL;
            gboolean retval = g_dbus_connection_send_message (
                                        bus_connection_get_dbus_connection (dest_connection),
                                        data->message,
                                        G_DBUS_SEND_MESSAGE_FLAGS_PRESERVE_SERIAL,
                                        NULL, &error);
            if (retval)
                break;
            g_warning ("forward message failed:  %s.", error->message);
            g_error_free (error);
        }

        if (g_dbus_message_get_message_type (data->message) != G_DBUS_MESSAGE_TYPE_METHOD_CALL) {

            break;
        }


        GDBusMessage *reply_message = g_dbus_message_new_method_error (data->message,
                            "org.freedesktop.DBus.Error.ServiceUnknown ",
                            "The service name is '%s'.", destination);
        g_dbus_message_set_sender (reply_message, "org.freedesktop.DBus");
        g_dbus_message_set_destination (reply_message, bus_connection_get_unique_name (data->sender_connection));
        g_dbus_connection_send_message (bus_connection_get_dbus_connection (data->sender_connection),
                                        reply_message,
                                        G_DBUS_SEND_MESSAGE_FLAGS_NONE,
                                        NULL, NULL);
        g_object_unref (reply_message);
    } while (0);

    g_object_unref (data->message);
    g_object_unref (data->sender_connection);
    g_slice_free (BusForwardData, data);
    return has_message;
}
