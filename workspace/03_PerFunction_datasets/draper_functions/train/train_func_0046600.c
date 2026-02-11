control_proxy_on_daemon_disappeared(bool clean_exit)
{
  log_info("ladishd disappeared");

  if (!clean_exit)
  {
    error_message_box("ladish daemon crashed");
    set_studio_state(STUDIO_STATE_SICK);
  }
  else
  {
    set_studio_state(STUDIO_STATE_NA);
  }

  studio_state_changed(NULL);

  if (studio_loaded())
  {
    destroy_studio_view();
  }

  world_tree_destroy_room_views();

  g_ladishd_poll_source_tag = g_timeout_add(500, poll_ladishd, NULL);
}
