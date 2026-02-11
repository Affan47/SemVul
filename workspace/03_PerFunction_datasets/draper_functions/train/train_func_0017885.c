bvw_handle_application_message (BaconVideoWidget *bvw, GstMessage *msg)
{
  const GstStructure *structure;
  const gchar *msg_name;

  structure = gst_message_get_structure (msg);
  msg_name = gst_structure_get_name (structure);
  g_return_if_fail (msg_name != NULL);

  GST_DEBUG ("Handling application message: %" GST_PTR_FORMAT, structure);

  if (strcmp (msg_name, "stream-changed") == 0) {
    bvw_update_stream_info (bvw);
  }
  else if (strcmp (msg_name, "video-size") == 0) {
    int w, h;

    g_signal_emit (bvw, bvw_signals[SIGNAL_GOT_METADATA], 0, NULL);


    get_media_size (bvw, &w, &h);
    clutter_actor_set_size (bvw->priv->texture, w, h);

    if (bvw->priv->auto_resize
	&& !bvw->priv->fullscreen_mode
	&& !bvw->priv->window_resized) {
      bacon_video_widget_set_scale_ratio (bvw, 0.0);
    }
    bvw->priv->window_resized = TRUE;
    set_current_actor (bvw);
  } else {
    g_debug ("Unhandled application message %s", msg_name);
  }
}
