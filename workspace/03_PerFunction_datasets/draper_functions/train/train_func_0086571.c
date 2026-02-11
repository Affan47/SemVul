end_time_check (gtk_video_private_t *priv)
{
  gint pos_stream, pos_time, length_time;
  priv->end_time_id = 0;
  if (!xine_get_pos_length (stream, &pos_stream, &pos_time, &length_time))
    pos_stream = pos_time = length_time = 0;
  if (priv->end_time && pos_time >= priv->end_time)
  {
    logprintf ("gtkvideo: end time passed, sending stop event\n");
    priv->end_time = 0;
    xine_stream_t *stream = priv->stream;
    xine_set_param (stream, XINE_PARAM_SPEED, XINE_SPEED_PAUSE);
    xine_event_t event = {
      .type = XINE_EVENT_UI_PLAYBACK_FINISHED,
      .stream = stream,
      .data = NULL
    };
    xine_event_send (stream, &event);
  }
  return FALSE;
}
