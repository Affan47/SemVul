ladish_write_vgraph(int fd, int indent, ladish_graph_handle vgraph, ladish_app_supervisor_handle app_supervisor)
{
  struct ladish_write_vgraph_context context;

  ladish_check_integrity();

  context.fd = fd;
  context.indent = indent + 1;
  context.app_supervisor = app_supervisor;

  if (!ladish_write_indented_string(fd, indent, "<clients>\n"))
  {
    return false;
  }

  if (!ladish_graph_iterate_nodes(
        vgraph,
        &context,
        ladish_save_vgraph_client_begin,
        ladish_save_vgraph_port,
        ladish_save_vgraph_client_end))
  {
    log_error("ladish_graph_iterate_nodes() failed");
    return false;
  }

  if (!ladish_write_indented_string(fd, indent, "</clients>\n"))
  {
    return false;
  }

  if (!ladish_write_indented_string(fd, indent, "<connections>\n"))
  {
    return false;
  }

  if (!ladish_graph_iterate_connections(vgraph, &context, ladish_save_vgraph_connection))
  {
    log_error("ladish_graph_iterate_connections() failed");
    return false;
  }

  if (!ladish_write_indented_string(fd, indent, "</connections>\n"))
  {
    return false;
  }

  if (!ladish_write_indented_string(fd, indent, "<applications>\n"))
  {
    return false;
  }

  if (!ladish_app_supervisor_enum(app_supervisor, &context, ladish_save_app))
  {
    return false;
  }

  if (!ladish_write_indented_string(fd, indent, "</applications>\n"))
  {
    return false;
  }

  return true;
}
