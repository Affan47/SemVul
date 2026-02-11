gst_rfb_src_dispose (GObject * object)
{
  GstRfbSrc *src = GST_RFB_SRC (object);

  g_free (src->host);
  if (src->decoder) {
    rfb_decoder_free (src->decoder);
    g_free (src->decoder);
    src->decoder = NULL;
  }

  G_OBJECT_CLASS (parent_class)->dispose (object);
}
