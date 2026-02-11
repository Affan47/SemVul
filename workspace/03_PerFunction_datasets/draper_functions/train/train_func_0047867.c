gst_byte_writer_free (GstByteWriter * writer)
{
  g_return_if_fail (writer != NULL);

  gst_byte_writer_reset (writer);
  g_slice_free (GstByteWriter, writer);
}
