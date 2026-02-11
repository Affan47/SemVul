gst_tcp_client_src_getcaps (GstBaseSrc * bsrc)
{
  GstTCPClientSrc *src;
  GstCaps *caps = NULL;

  src = GST_TCP_CLIENT_SRC (bsrc);

  if (!GST_OBJECT_FLAG_IS_SET (src, GST_TCP_CLIENT_SRC_OPEN))
    caps = gst_caps_new_any ();
  else if (src->caps)
    caps = gst_caps_copy (src->caps);
  else
    caps = gst_caps_new_any ();
  GST_DEBUG_OBJECT (src, "returning caps %" GST_PTR_FORMAT, caps);
  g_assert (GST_IS_CAPS (caps));
  return caps;
}
