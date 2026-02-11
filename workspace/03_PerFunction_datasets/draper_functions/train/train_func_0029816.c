gst_check_drop_buffers (void)
{
  while (buffers != NULL) {
    gst_buffer_unref (GST_BUFFER (buffers->data));
    buffers = g_list_delete_link (buffers, buffers);
  }
}
