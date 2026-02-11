e_msgbus_init(void)
{
   E_DBus_Interface *iface;

   _e_msgbus_data = E_NEW(E_Msgbus_Data, 1);

   e_dbus_init();
#ifdef HAVE_HAL
   e_hal_init();
#endif

   _e_msgbus_data->conn = e_dbus_bus_get(DBUS_BUS_SESSION);
   if (!_e_msgbus_data->conn)
     {
        WRN("Cannot get DBUS_BUS_SESSION");
        return 0;
     }
   e_dbus_request_name(_e_msgbus_data->conn, "org.enlightenment.wm.service", 0, _e_msgbus_request_name_cb, NULL);
   _e_msgbus_data->obj = e_dbus_object_add(_e_msgbus_data->conn, "/org/enlightenment/wm/RemoteObject", NULL);

   iface = e_dbus_interface_new("org.enlightenment.wm.Core");
   if (!iface)
     {
        WRN("Cannot add org.enlightenment.wm.Core interface");
        return 0;
     }
   e_dbus_object_interface_attach(_e_msgbus_data->obj, iface);
   e_dbus_interface_unref(iface);


   e_dbus_interface_method_add(iface, "Restart", "", "", _e_msgbus_core_restart_cb);
   e_dbus_interface_method_add(iface, "Shutdown", "", "", _e_msgbus_core_shutdown_cb);

   iface = e_dbus_interface_new("org.enlightenment.wm.Module");
   if (!iface)
     {
        WRN("Cannot add org.enlightenment.wm.Module interface");
        return 0;
     }
   e_dbus_object_interface_attach(_e_msgbus_data->obj, iface);
   e_dbus_interface_unref(iface);


   e_dbus_interface_method_add(iface, "Load", "s", "", _e_msgbus_module_load_cb);
   e_dbus_interface_method_add(iface, "Unload", "s", "", _e_msgbus_module_unload_cb);
   e_dbus_interface_method_add(iface, "Enable", "s", "", _e_msgbus_module_enable_cb);
   e_dbus_interface_method_add(iface, "Disable", "s", "", _e_msgbus_module_disable_cb);
   e_dbus_interface_method_add(iface, "List", "", "a(si)", _e_msgbus_module_list_cb);

   iface = e_dbus_interface_new("org.enlightenment.wm.Profile");
   if (!iface)
     {
        WRN("Cannot add org.enlightenment.wm.Profile interface");
        return 0;
     }
   e_dbus_object_interface_attach(_e_msgbus_data->obj, iface);
   e_dbus_interface_unref(iface);


   e_dbus_interface_method_add(iface, "Set", "s", "", _e_msgbus_profile_set_cb);
   e_dbus_interface_method_add(iface, "Get", "", "s", _e_msgbus_profile_get_cb);
   e_dbus_interface_method_add(iface, "List", "", "as", _e_msgbus_profile_list_cb);
   e_dbus_interface_method_add(iface, "Add", "s", "", _e_msgbus_profile_add_cb);
   e_dbus_interface_method_add(iface, "Delete", "s", "", _e_msgbus_profile_delete_cb);

   iface = e_dbus_interface_new("org.enlightenment.wm.Window");
   if (!iface)
     {
        WRN("Cannot add org.enlightenment.wm.Window interface");
        return 0;
     }
   e_dbus_object_interface_attach(_e_msgbus_data->obj, iface);
   e_dbus_interface_unref(iface);


   e_dbus_interface_method_add(iface, "List", "", "a(si)", _e_msgbus_window_list_cb);
   e_dbus_interface_method_add(iface, "Close", "i", "", _e_msgbus_window_close_cb);
   e_dbus_interface_method_add(iface, "Kill", "i", "", _e_msgbus_window_kill_cb);
   e_dbus_interface_method_add(iface, "Focus", "i", "", _e_msgbus_window_focus_cb);
   e_dbus_interface_method_add(iface, "Iconify", "i", "", _e_msgbus_window_iconify_cb);
   e_dbus_interface_method_add(iface, "Uniconify", "i", "", _e_msgbus_window_uniconify_cb);
   e_dbus_interface_method_add(iface, "Maximize", "i", "", _e_msgbus_window_maximize_cb);
   e_dbus_interface_method_add(iface, "Unmaximize", "i", "", _e_msgbus_window_unmaximize_cb);

   return 1;
}
