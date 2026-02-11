interlink_port(
  void * context,
  ladish_graph_handle graph_handle,
  bool hidden,
  void * client_iteration_context_ptr,
  ladish_client_handle client_handle,
  const char * client_name,
  ladish_port_handle port_handle,
  const char * port_name,
  uint32_t port_type,
  uint32_t port_flags)
{
  uuid_t app_uuid;

  if (ladish_client_get_app(client_handle, app_uuid))
  {
    ladish_port_set_app(port_handle, app_uuid);
  }

  return true;
}
