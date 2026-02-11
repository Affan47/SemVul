ibus_engine_new_with_type (GType            engine_type,
                           const gchar     *engine_name,
                           const gchar     *object_path,
                           GDBusConnection *connection)
{
    g_return_val_if_fail (g_type_is_a (engine_type, IBUS_TYPE_ENGINE), NULL);
    g_return_val_if_fail (engine_name != NULL, NULL);
    g_return_val_if_fail (object_path != NULL, NULL);
    g_return_val_if_fail (G_IS_DBUS_CONNECTION (connection), NULL);

    GObject *object = g_object_new (engine_type,
                                    "engine-name", engine_name,
                                    "object-path", object_path,
                                    "connection", connection,
                                    NULL);
    return IBUS_ENGINE (object);
}
