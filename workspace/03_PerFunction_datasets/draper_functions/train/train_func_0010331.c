gst_rfb_src_stop (GstBaseSrc * bsrc)
{
  GstRfbSrc *src = GST_RFB_SRC (bsrc);

  if (src->decoder->socket) {
    g_object_unref (src->decoder->socket);
    src->decoder->socket = NULL;
  }

  if (src->decoder->frame) {
    g_free (src->decoder->frame);
    src->decoder->frame = NULL;
  }

  if (src->decoder->prev_frame) {
    g_free (src->decoder->prev_frame);
    src->decoder->prev_frame = NULL;
  }

  return TRUE;
}
