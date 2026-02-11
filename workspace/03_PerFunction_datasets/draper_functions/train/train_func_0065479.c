gst_istximage_src_stop (GstBaseSrc * basesrc)
{
  GstIstXImageSrc *src = GST_ISTXIMAGE_SRC (basesrc);

  gst_istximage_src_clear_bufpool (src);

  if (src->xcontext) {
    g_mutex_lock (src->x_lock);
    istximageutil_xcontext_clear (src->xcontext);
    src->xcontext = NULL;
    g_mutex_unlock (src->x_lock);
  }

  return TRUE;
}
