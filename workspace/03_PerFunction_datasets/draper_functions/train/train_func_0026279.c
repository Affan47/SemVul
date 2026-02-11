ibus_service_service_method_call (IBusService           *service,
                                  GDBusConnection       *connection,
                                  const gchar           *sender,
                                  const gchar           *object_path,
                                  const gchar           *interface_name,
                                  const gchar           *method_name,
                                  GVariant              *parameters,
                                  GDBusMethodInvocation *invocation)
{
    if (g_strcmp0 (method_name, "Destroy") == 0) {
        g_dbus_method_invocation_return_value (invocation, NULL);
        ibus_object_destroy ((IBusObject *)service);
        return;
    }

    g_dbus_method_invocation_return_error (invocation,
                                           G_DBUS_ERROR,
                                           G_DBUS_ERROR_UNKNOWN_METHOD,
                                           "%s::%s", interface_name, method_name);
    return;
}
