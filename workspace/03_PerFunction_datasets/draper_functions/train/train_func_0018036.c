frame_event_cb (CoglOnscreen *onscreen,
                CoglFrameEvent event,
                CoglFrameInfo *info,
                void *user_data)
{
  Data *data = user_data;

  if (event == COGL_FRAME_EVENT_SYNC)
    data->swap_ready = TRUE;
}
