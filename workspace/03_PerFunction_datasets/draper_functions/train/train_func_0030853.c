gst_soup_http_src_unlock (GstBaseSrc * bsrc)
{
  GstSoupHTTPSrc *src;

  src = GST_SOUP_HTTP_SRC (bsrc);
  GST_DEBUG_OBJECT (src, "unlock()");

  src->interrupted = TRUE;
  if (src->loop)
    g_main_loop_quit (src->loop);
  g_cond_signal (&src->request_finished_cond);
  return TRUE;
}
