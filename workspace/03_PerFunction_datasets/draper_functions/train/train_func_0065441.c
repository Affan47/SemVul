graph_proxy_dict_entry_drop(
  graph_proxy_handle graph,
  uint32_t object_type,
  uint64_t object_id,
  const char * key)
{
  if (!graph_ptr->graph_dict_supported)
  {
    return false;
  }

  if (!cdbus_call(0, graph_ptr->service, graph_ptr->object, IFACE_GRAPH_DICT, "Drop", "uts", &object_type, &object_id, &key, ""))
  {
    log_error(IFACE_GRAPH_DICT ".Drop() failed.");
    return false;
  }

  return true;
}
