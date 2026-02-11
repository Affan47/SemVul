gst_mpegvideoparse_flush_decode (MpegVideoParse * mpegvideoparse, guint idx)
{
  GstFlowReturn res = GST_FLOW_OK;
  GstBuffer *head = NULL;

  while (mpegvideoparse->decode) {
    GstBuffer *buf;

    buf = GST_BUFFER_CAST (mpegvideoparse->decode->data);

    if (idx != -1) {
      GstBuffer *temp;

      if (idx > 0) {


        head = gst_buffer_create_sub (buf, 0, idx);


        temp = gst_buffer_create_sub (buf, idx, GST_BUFFER_SIZE (buf) - idx);

        gst_buffer_unref (buf);
        buf = temp;
      }
      GST_BUFFER_FLAG_SET (buf, GST_BUFFER_FLAG_DISCONT);
      idx = -1;
    } else {

      GST_BUFFER_FLAG_UNSET (buf, GST_BUFFER_FLAG_DISCONT);
    }

    GST_DEBUG_OBJECT (mpegvideoparse, "pushing buffer %p, ts %" GST_TIME_FORMAT,
        buf, GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (buf)));

    res = gst_pad_push (mpegvideoparse->srcpad, buf);

    mpegvideoparse->decode =
        g_list_delete_link (mpegvideoparse->decode, mpegvideoparse->decode);
  }
  if (head) {

    mpegvideoparse->decode = g_list_prepend (mpegvideoparse->decode, head);
  }
  return res;
}
