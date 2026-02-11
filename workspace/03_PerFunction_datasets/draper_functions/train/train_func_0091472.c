audio_tags_changed_cb (GstElement *playbin2, gint stream_id, gpointer user_data)
{
  BaconVideoWidget *bvw = (BaconVideoWidget *) user_data;
  GstTagList *tags = NULL;
  gint current_stream_id = 0;

  g_object_get (G_OBJECT (bvw->priv->play), "current-audio", &current_stream_id, NULL);


  if (current_stream_id != stream_id)
    return;

  g_signal_emit_by_name (G_OBJECT (bvw->priv->play), "get-audio-tags", stream_id, &tags);

  if (tags)
    bvw_update_tags_delayed (bvw, tags, "audio");
}
