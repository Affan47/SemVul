gst_dccp_client_src_create (GstPushSrc * psrc, GstBuffer ** outbuf)
{
  GstDCCPClientSrc *src;
  GstFlowReturn ret = GST_FLOW_OK;

  src = GST_DCCP_CLIENT_SRC (psrc);

  GST_LOG_OBJECT (src, "reading a buffer");
  ret = gst_dccp_read_buffer (GST_ELEMENT (src), src->sock_fd, outbuf);

  if (ret == GST_FLOW_OK) {
    GST_LOG_OBJECT (src,
        "Returning buffer from _get of size %d, ts %"
        GST_TIME_FORMAT ", dur %" GST_TIME_FORMAT
        ", offset %" G_GINT64_FORMAT ", offset_end %" G_GINT64_FORMAT,
        GST_BUFFER_SIZE (*outbuf),
        GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (*outbuf)),
        GST_TIME_ARGS (GST_BUFFER_DURATION (*outbuf)),
        GST_BUFFER_OFFSET (*outbuf), GST_BUFFER_OFFSET_END (*outbuf));

    if (!gst_caps_is_equal (src->caps, GST_CAPS_ANY)) {
      gst_buffer_set_caps (*outbuf, src->caps);
    }
  }

  return ret;
}
