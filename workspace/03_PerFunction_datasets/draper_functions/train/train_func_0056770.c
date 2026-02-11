register_prog(const char* prog_name, PresentFunc func, void* object_data) {


  static bool initialised = false;


  static gboolean return_val = FALSE;

  if (initialised) {
    g_warning("Only call register_prog() once in any one program instance - ignoring this call\n");
    return return_val;
  }
  initialised = true;

  GError* error = 0;


  session_connection = g_bus_get_sync(G_BUS_TYPE_SESSION, 0, &error);
  if (!session_connection) {

    g_critical("Failed to open connection to bus: %s\n", error->message);
    g_error_free(error);
    return return_val;
  }


  g_object_set(session_connection,
	       "exit-on-close", false,
	       static_cast<void*>(0));

  gchar* delimited_prog_name = g_strdup(prog_name);
  g_strdelimit(delimited_prog_name, "-|<>./+", '_');
  register_service = g_strdup_printf("%s.%s", REGISTER_SERVICE_PREFIX, delimited_prog_name);
  register_path = g_strdup_printf("%s/%s/%s", REGISTER_PATH_PREFIX, delimited_prog_name, "presenter");
  g_free(delimited_prog_name);

  GobjHandle<GDBusProxy> proxy(g_dbus_proxy_new_sync(session_connection,
						     G_DBUS_PROXY_FLAGS_NONE,
						     0,
						     CGU_DBUS_SERVICE,
						     CGU_DBUS_PATH,
						     CGU_DBUS_INTERFACE,
						     0,
						     &error));

  if (!proxy.get()) {

    g_critical("Failed to create proxy object: %s\n", error->message);
    g_error_free(error);
    clean_up_dbus_variables();
    return return_val;
  }

  GvarHandle result(g_dbus_proxy_call_sync(proxy,
					   "RequestName",
					   g_variant_new("(su)", register_service, 0),
					   G_DBUS_CALL_FLAGS_NONE,
					   -1,
					   0,
					   &error));
  if (!result.get()) {

    if (g_dbus_error_is_remote_error(error)) {
      gchar* dbus_msg = g_dbus_error_get_remote_error(error);
      if (dbus_msg) {
	g_critical("Dbus error: %s", dbus_msg);
	g_dbus_error_strip_remote_error(error);
	g_free(dbus_msg);
      }
    }
    g_critical("Failed to obtain name %s on session bus: %s", register_service, error->message);
    g_error_free(error);
    clean_up_dbus_variables();
    return return_val;
  }
  if (g_variant_get_uint32(GvarHandle(g_variant_get_child_value(result, 0)))
      != CGU_DBUS_BECOME_PRIMARY_OWNER) {

    return return_val;
  }


  GDBusNodeInfo* introspection_data = g_dbus_node_info_new_for_xml(introspection_xml, 0);
  if (!introspection_data) {
    g_critical("Failed to create introspection data for GDBus\n");
    clean_up_dbus_variables();
    return return_val;
  }
  cgu_present_items.func = func;
  cgu_present_items.data = object_data;

  guint id = g_dbus_connection_register_object(session_connection,
					       register_path,
					       introspection_data->interfaces[0],
					       &cgu_prog_presenter_interface_vtable,
					       0,
					       0,
					       &error);
  if (!id) {

    g_critical("Failed to register dbus object at path %s on session bus: %s",
	       register_path, error->message);
    g_error_free(error);
    clean_up_dbus_variables();
    g_dbus_node_info_unref(introspection_data);
    return return_val;
  }


  clean_up_dbus_variables();
  g_dbus_node_info_unref(introspection_data);

  return_val = TRUE;
  return return_val;
}
