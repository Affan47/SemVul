pad_link_maybe_ghosting (GstPad * src, GstPad * sink, GstPadLinkCheck flags)
{
  GSList *pads_created = NULL;
  gboolean ret;

  if (!prepare_link_maybe_ghosting (&src, &sink, &pads_created)) {
    ret = FALSE;
  } else {
    ret = (gst_pad_link_full (src, sink, flags) == GST_PAD_LINK_OK);
  }

  if (!ret) {
    g_slist_foreach (pads_created, remove_pad, NULL);
  }
  g_slist_free (pads_created);

  return ret;
}
