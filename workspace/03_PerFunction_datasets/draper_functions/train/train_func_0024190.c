stream_remove_updater (Stream* stream)
{
  if (stream->update_function_source_id != 0)
  {
    g_debug ("%s: removing update function", __FUNCTION__);
    g_source_remove (stream->update_function_source_id);
    stream->update_function_source_id = 0;
  }
}
