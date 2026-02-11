gst_au_parse_remove_srcpad (GstAuParse * auparse)
{
  gboolean res = TRUE;

  if (auparse->srcpad != NULL) {
    GST_DEBUG_OBJECT (auparse, "Removing src pad");
    res = gst_element_remove_pad (GST_ELEMENT (auparse), auparse->srcpad);
    g_return_val_if_fail (res != FALSE, FALSE);
    gst_object_unref (auparse->srcpad);
    auparse->srcpad = NULL;
  }

  return res;
}
