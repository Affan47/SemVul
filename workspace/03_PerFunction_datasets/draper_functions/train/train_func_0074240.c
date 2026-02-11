force_update_now (MatewnckWindow *window)
{
  MatewnckWindowState old_state;
  MatewnckWindowState new_state;
  MatewnckWindowActions old_actions;

  unqueue_update (window);


  update_name (window);
  update_icon_name (window);

  if (window->priv->need_emit_name_changed)
    emit_name_changed (window);

  old_state = COMPRESS_STATE (window);
  old_actions = window->priv->actions;

  update_startup_id (window);
  update_wmclass (window);
  update_wmhints (window);
  update_transient_for (window);
  update_wintype (window);
  update_wm_state (window);
  update_state (window);


  update_workspace (window);
  update_actions (window);
  update_frame_extents (window);

  get_icons (window);

  new_state = COMPRESS_STATE (window);

  if (old_state != new_state)
    emit_state_changed (window, old_state ^ new_state, new_state);

  if (old_actions != window->priv->actions)
    emit_actions_changed (window, old_actions ^ window->priv->actions,
                          window->priv->actions);

  if (window->priv->need_emit_icon_changed)
    emit_icon_changed (window);
}
