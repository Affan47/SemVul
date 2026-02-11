rsn_wrapped_buffer_default_release (GstElement * owner, RsnWrappedBuffer * buf)
{
  g_return_val_if_fail (buf != NULL, FALSE);
  g_return_val_if_fail (buf->wrapped_buffer != NULL, FALSE);

  gst_buffer_unref (buf->wrapped_buffer);
  if (buf->owner)
    gst_object_unref (buf->owner);

  return FALSE;
}
