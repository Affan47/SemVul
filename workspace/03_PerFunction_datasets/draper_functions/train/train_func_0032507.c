_free_pending_clip (GESBaseXmlFormatterPrivate * priv, PendingClip * pend)
{
  gst_object_unref (pend->layer);
  if (pend->properties)
    gst_structure_free (pend->properties);
  g_list_free_full (pend->effects, (GDestroyNotify) _free_pending_effect);
  g_list_free_full (pend->pending_bindings,
      (GDestroyNotify) _free_pending_binding);
  g_hash_table_remove (priv->clipid_pendings, pend->id);
  g_free (pend->id);
  g_slice_free (PendingClip, pend);
}
