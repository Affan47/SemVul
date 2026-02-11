on_name_acquired(GDBusConnection *conn, const gchar *name, gpointer data)
{
    GDBusInterfaceInfo *iface;
    GError *error = NULL;
    unsigned id;
    scanner_t *scanner;

    scanner = g_new0(scanner_t, 1);
    g_assert(scanner != NULL);
    scanner->conn = conn;
    scanner->pending_scan = NULL;
    scanner->update_id = get_update_id();

    iface = g_dbus_node_info_lookup_interface(introspection_data, BUS_IFACE);

    id = g_dbus_connection_register_object(conn,
                                           BUS_PATH,
                                           iface,
                                           &scanner_vtable,
                                           scanner,
                                           scanner_destroyed,
                                           NULL);
    g_assert(id > 0);

    scanner->mounts.channel = g_io_channel_new_file("/proc/self/mountinfo",
                                                    "r", &error);
    if (error) {
      g_warning("No /proc/self/mountinfo file: %s. Disabled mount monitoring.",
                error->message);
      g_error_free(error);
    } else {
        scanner->mounts.watch = g_io_add_watch(scanner->mounts.channel,
                                               G_IO_ERR,
                                               on_mounts_changed, scanner);
        scanner->mounts.paths = scanner_mounts_parse(scanner);
    }

    if (startup_scan) {
        g_debug("Do startup scan");
        g_hash_table_foreach(categories, scan_params_all, scanner);
        do_scan(scanner);
    }

    scanner_update_id_changed(scanner);
    scanner_write_lock_changed(scanner);
    scanner_is_scanning_changed(scanner);
    scanner_categories_changed(scanner);

    g_debug("Acquired name org.lightmediascanner and registered object");
}
