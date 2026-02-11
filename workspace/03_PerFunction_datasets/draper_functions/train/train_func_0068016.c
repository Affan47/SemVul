device_mobile_device_got_modem_manager_cb (GObject *source_object,
                                   GAsyncResult *res,
                                   gpointer user_data)
{
        GError *error = NULL;
        GVariant *result = NULL;
        GDBusProxy *proxy;
        NMDevice *device = (NMDevice *) user_data;

        proxy = g_dbus_proxy_new_for_bus_finish (res, &error);
        if (proxy == NULL) {
                g_warning ("Error creating ModemManager proxy: %s",
                           error->message);
                g_error_free (error);
                goto out;
        }


        result = g_dbus_proxy_get_cached_property (proxy,
                                                   "EquipmentIdentifier");


        g_object_set_data_full (G_OBJECT (device),
                                "ControlCenter::EquipmentIdentifier",
                                g_variant_dup_string (result, NULL),
                                g_free);
out:
        if (result != NULL)
                g_variant_unref (result);
        if (proxy != NULL)
                g_object_unref (proxy);
}
