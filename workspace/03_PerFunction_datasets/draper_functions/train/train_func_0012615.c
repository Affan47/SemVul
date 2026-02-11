room_disappeared(const char * opath, const char * name, const char * template)
{
  graph_view_handle graph_view;

  log_info("room \"%s\" disappeared (%s). template is \"%s\"", name, opath, template);

  graph_view = world_tree_find_by_opath(opath);
  if (graph_view == NULL)
  {
    log_error("Unknown room disappeared");
    return;
  }

  destroy_view(graph_view);
}
