gst_gdp_pay_reset (GstGDPPay * this)
{
  GST_DEBUG_OBJECT (this, "Resetting GDP object");

  while (this->queue) {
    GstBuffer *buffer;

    buffer = GST_BUFFER_CAST (this->queue->data);


    this->queue = g_list_delete_link (this->queue, this->queue);

    gst_buffer_unref (buffer);
  }
  if (this->caps) {
    gst_caps_unref (this->caps);
    this->caps = NULL;
  }
  if (this->caps_buf) {
    gst_buffer_unref (this->caps_buf);
    this->caps_buf = NULL;
  }
  if (this->tag_buf) {
    gst_buffer_unref (this->tag_buf);
    this->tag_buf = NULL;
  }
  if (this->new_segment_buf) {
    gst_buffer_unref (this->new_segment_buf);
    this->new_segment_buf = NULL;
  }
  this->sent_streamheader = FALSE;
  this->offset = 0;
}
