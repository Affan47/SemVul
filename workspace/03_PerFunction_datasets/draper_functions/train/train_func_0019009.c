on_popup_menu_action_app_start(GtkWidget * menuitem, gpointer userdata)
{
  uint64_t id;
  ladish_app_supervisor_proxy_handle proxy;
  graph_view_handle view;

  if (!get_selected_app_id(&view, &id))
  {
    return;
  }

  log_info("start app %"PRIu64, id);

  proxy = graph_view_get_app_supervisor(view);
  ladish_app_supervisor_proxy_start_app(proxy, id);
}
