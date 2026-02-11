graph_canvas_create(
  int width,
  int height,
  void (* fill_canvas_menu_callback)(GtkMenu * menu),
  graph_canvas_handle * graph_canvas_handle_ptr)
{
  struct graph_canvas * graph_canvas_ptr;

  graph_canvas_ptr = malloc(sizeof(struct graph_canvas));
  if (graph_canvas_ptr == NULL)
  {
    return false;
  }

  graph_canvas_ptr->fill_menu = fill_canvas_menu_callback;

  if (!canvas_create(
        width,
        height,
        graph_canvas_ptr,
        connect_request,
        disconnect_request,
        module_location_changed,
        fill_canvas_menu,
        fill_module_menu,
        fill_port_menu,
        &graph_canvas_ptr->canvas))
  {
    free(graph_canvas_ptr);
    return false;
  }

  graph_canvas_ptr->graph = NULL;
  INIT_LIST_HEAD(&graph_canvas_ptr->clients);

  *graph_canvas_handle_ptr = (graph_canvas_handle)graph_canvas_ptr;

  return true;
}
