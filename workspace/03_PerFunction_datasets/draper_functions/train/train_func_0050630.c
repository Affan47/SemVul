rsn_wrapped_buffer_set_owner (RsnWrappedBuffer * wrapped_buf,
    GstElement * owner)
{
  g_return_if_fail (wrapped_buf != NULL);

  if (wrapped_buf->owner)
    gst_object_unref (wrapped_buf->owner);

  if (owner)
    wrapped_buf->owner = gst_object_ref (owner);
  else
    wrapped_buf->owner = NULL;
}
