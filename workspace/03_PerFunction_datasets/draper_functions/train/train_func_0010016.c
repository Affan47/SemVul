save_result (GstElement * sink, GstBuffer * buf, GstPad * pad, gpointer data)
{
  GstBuffer **p_buf = (GstBuffer **) data;

  *p_buf = gst_buffer_ref (buf);

  GST_DEBUG ("received converted buffer %p with caps %" GST_PTR_FORMAT,
      *p_buf, GST_BUFFER_CAPS (*p_buf));
}
