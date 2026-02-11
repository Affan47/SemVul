convert_frame_new_buffer_callback (GstElement * sink,
    GstVideoConvertFrameContext * context)
{
  GstBuffer *buf = NULL;
  GError *error = NULL;

  g_mutex_lock (context->mutex);

  if (context->finished)
    goto done;

  g_signal_emit_by_name (sink, "pull-preroll", &buf);

  if (!buf) {
    error = g_error_new (GST_CORE_ERROR, GST_CORE_ERROR_FAILED,
        "Could not get converted video frame");
  }

  convert_frame_finish (context, buf, error);

  g_signal_handlers_disconnect_by_func (sink, convert_frame_need_data_callback,
      context);

done:
  g_mutex_unlock (context->mutex);
}
