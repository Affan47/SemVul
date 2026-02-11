on_videooutput_device_opened_cb (Ekiga::VideoOutputManager & ,
                                 Ekiga::VideoOutputAccel ,
                                 Ekiga::VideoOutputMode mode,
                                 unsigned zoom,
                                 bool both_streams,
                                 bool ext_stream,
                                 gpointer self)
{
  EkigaCallWindow *cw = EKIGA_CALL_WINDOW (self);
  int vv;

  if (both_streams) {
    gtk_menu_section_set_sensitive (cw->priv->main_menu, "local_video", true);
    gtk_menu_section_set_sensitive (cw->priv->main_menu, "fullscreen", true);
  }
  else {
    if (mode == Ekiga::VO_MODE_LOCAL)
      gtk_menu_set_sensitive (cw->priv->main_menu, "local_video", true);
    else if (mode == Ekiga::VO_MODE_REMOTE)
      gtk_menu_set_sensitive (cw->priv->main_menu, "remote_video", true);
  }

  gtk_menu_set_sensitive (cw->priv->main_menu, "extended_video", ext_stream);


  vv = gm_conf_get_int (VIDEO_DISPLAY_KEY "video_view");
  cw->priv->changing_back_to_local_after_a_call = true;
  gtk_radio_menu_select_with_id (cw->priv->main_menu, "local_video", mode);
  cw->priv->changing_back_to_local_after_a_call = false;
  if (!both_streams && mode == Ekiga::VO_MODE_LOCAL)
    gm_conf_set_int (VIDEO_DISPLAY_KEY "video_view", vv);


  if (vv == Ekiga::VO_MODE_REMOTE_EXT && !ext_stream)
    gm_conf_set_int (VIDEO_DISPLAY_KEY "video_view", Ekiga::VO_MODE_LOCAL);

  ekiga_call_window_zooms_menu_update_sensitivity (cw, zoom);
}
