gst_ghost_pad_get_target (GstGhostPad * gpad)
{
  GstPad *ret;

  g_return_val_if_fail (GST_IS_GHOST_PAD (gpad), NULL);

  ret = gst_proxy_pad_get_target (GST_PAD_CAST (gpad));

  GST_DEBUG_OBJECT (gpad, "get target %s:%s", GST_DEBUG_PAD_NAME (ret));

  return ret;
}
