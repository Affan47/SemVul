ladish_save_vgraph_client_begin(
  void * context,
  ladish_graph_handle graph,
  bool hidden,
  ladish_client_handle client_handle,
  const char * client_name,
  void ** client_iteration_context_ptr_ptr)
{
  uuid_t uuid;
  char str[37];
  uuid_t app_uuid;
  char app_str[37];

  ctx_ptr->client_visible = !hidden;
  if (!ctx_ptr->client_visible)
  {
    if (ladish_client_has_app(client_handle))
    {
      ctx_ptr->client_visible = true;
      log_info("saving hidden vgraph client '%s' of managed app", client_name);
    }
    else
    {
      log_info("not saving hidden vgraph client '%s' because it has no app associated", client_name);
    }
  }

  if (!ctx_ptr->client_visible)
  {
    return true;
  }

  ladish_client_get_uuid(client_handle, uuid);
  uuid_unparse(uuid, str);

  log_info("saving vgraph client '%s' (%s)", client_name, str);

  if (!ladish_write_indented_string(fd, indent, "<client name=\""))
  {
    return false;
  }

  if (!ladish_write_string_escape_ex(fd, client_name, LADISH_ESCAPE_FLAG_XML_ATTR))
  {
    return false;
  }

  if (!ladish_write_string(fd, "\" uuid=\""))
  {
    return false;
  }

  if (!ladish_write_string(fd, str))
  {
    return false;
  }

  if (!ladish_write_string(fd, "\" naming=\""))
  {
    return false;
  }

  if (!ladish_write_string(fd, "app"))
  {
    return false;
  }

  if (ladish_client_get_app(client_handle, app_uuid))
  {
    uuid_unparse(app_uuid, app_str);

    if (!ladish_write_string(fd, "\" app=\""))
    {
      return false;
    }

    if (!ladish_write_string(fd, app_str))
    {
      return false;
    }
  }

  if (!ladish_write_string(fd, "\">\n"))
  {
    return false;
  }

  if (!ladish_write_indented_string(fd, indent + 1, "<ports>\n"))
  {
    return false;
  }

  return true;
}
