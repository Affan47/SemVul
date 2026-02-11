ladish_studio_show(void)
{
  cdbus_object_path object;

  ASSERT(g_studio.name != NULL);
  ASSERT(!g_studio.announced);

  object = cdbus_object_path_new(
    STUDIO_OBJECT_PATH,
    &g_interface_studio, &g_studio,
    &g_interface_patchbay, ladish_graph_get_dbus_context(g_studio.studio_graph),
    &g_iface_graph_dict, g_studio.studio_graph,
    &g_iface_graph_manager, g_studio.studio_graph,
    &g_iface_app_supervisor, g_studio.app_supervisor,
    NULL);
  if (object == NULL)
  {
    log_error("cdbus_object_path_new() failed");
    return false;
  }

  if (!cdbus_object_path_register(cdbus_g_dbus_connection, object))
  {
    log_error("object_path_register() failed");
    cdbus_object_path_destroy(cdbus_g_dbus_connection, object);
    return false;
  }

  log_info("Studio D-Bus object created. \"%s\"", g_studio.name);

  g_studio.dbus_object = object;

  emit_studio_appeared();

  return true;
}
