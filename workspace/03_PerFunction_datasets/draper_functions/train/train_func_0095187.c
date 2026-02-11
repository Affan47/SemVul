do_update_now (MatewnckScreen *screen)
{
  if (screen->priv->update_handler)
    {
      g_source_remove (screen->priv->update_handler);
      screen->priv->update_handler = 0;
    }


  if (screen->priv->need_update_workspace_list)
    {
      screen->priv->need_update_viewport_settings = TRUE;
      screen->priv->need_update_workspace_names = TRUE;
    }


  update_workspace_list (screen);
  update_client_list (screen);


  update_active_workspace (screen);
  update_viewport_settings (screen);
  update_active_window (screen);
  update_workspace_layout (screen);
  update_workspace_names (screen);
  update_showing_desktop (screen);
  update_wm (screen);

  update_bg_pixmap (screen);
}
