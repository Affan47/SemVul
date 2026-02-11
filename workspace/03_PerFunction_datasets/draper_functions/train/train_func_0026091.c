do_async_done (GstSubtitleOverlay * self)
{
  if (self->do_async) {
    GstMessage *msg = gst_message_new_async_done (GST_OBJECT_CAST (self));

    GST_DEBUG_OBJECT (self, "Posting async-done");
    parent_class->handle_message (GST_BIN_CAST (self), msg);
    self->do_async = FALSE;
  }
}
