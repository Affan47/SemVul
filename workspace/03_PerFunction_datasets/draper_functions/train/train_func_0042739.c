announce_view_name_change(struct graph_view * view_ptr)
{
  world_tree_name_changed((graph_view_handle)view_ptr);

  if (g_current_view == view_ptr)
  {
    set_main_window_title((graph_view_handle)view_ptr);
  }

  menu_view_changed();
}
