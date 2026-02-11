dbus_scanner_scan(GDBusMethodInvocation *inv, scanner_t *scanner, GVariant *params)
{
    if (scanner->thread) {
        g_dbus_method_invocation_return_dbus_error(
            inv, "org.lightmediascanner.AlreadyScanning",
            "Scanner was already scanning.");
        return;
    }

    if (scanner->write_lock) {
        g_dbus_method_invocation_return_dbus_error(
            inv, "org.lightmediascanner.WriteLocked",
            "Data Base has a write lock for another process.");
        return;
    }

    dbus_scanner_scan_params_set(scanner, params);

    do_scan(scanner);

    g_dbus_method_invocation_return_value(inv, NULL);
}
