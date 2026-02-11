stream_data_free (StreamData * data)
{
  if (data) {
    gst_buffer_unmap (data->buffer, &data->map_info);
    gst_buffer_unref (data->buffer);
    g_free (data);
  }
}
