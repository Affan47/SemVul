gst_soup_http_src_check_seekable (GstSoupHTTPSrc * src)
{
  GstFlowReturn ret = GST_FLOW_OK;


  if (!src->got_headers && GST_STATE (src) >= GST_STATE_PAUSED) {
    g_mutex_lock (&src->mutex);
    while (!src->got_headers && !src->interrupted && ret == GST_FLOW_OK) {
      if ((src->msg && src->msg->method != SOUP_METHOD_HEAD) &&
          src->session_io_status != GST_SOUP_HTTP_SRC_SESSION_IO_STATUS_IDLE) {

        g_cond_wait (&src->request_finished_cond, &src->mutex);
      } else {
        if (gst_soup_http_src_session_open (src)) {
          ret = gst_soup_http_src_do_request (src, SOUP_METHOD_HEAD, NULL);
        }
      }
    }
    if (src->ret == GST_FLOW_EOS) {

      src->ret = GST_FLOW_OK;
    }

    gst_soup_http_src_cancel_message (src);
    g_mutex_unlock (&src->mutex);
  }

}
