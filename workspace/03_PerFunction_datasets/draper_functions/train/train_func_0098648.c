gnl_object_remove_ghost_pad (GnlObject * object, GstPad * ghost)
{
  GnlPadPrivate *priv;

  GST_DEBUG_OBJECT (object, "ghostpad %s:%s", GST_DEBUG_PAD_NAME (ghost));

  priv = gst_pad_get_element_private (ghost);
  gst_ghost_pad_set_target (GST_GHOST_PAD (ghost), NULL);
  gst_element_remove_pad (GST_ELEMENT (object), ghost);
  if (priv)
    g_slice_free (GnlPadPrivate, priv);
}
