_web_view_loaded_idle (PhotoData *data)
{
  data->idle_id = 0;
  if (data->timeout_id > 0) {
    g_source_remove (data->timeout_id);
    data->timeout_id = 0;
  }

  if (data->delay > 0)
    data->delay_id = g_timeout_add_seconds (data->delay,
                                            (GSourceFunc) _on_delay, data);
  else
    _on_delay (data);

  return FALSE;
}
