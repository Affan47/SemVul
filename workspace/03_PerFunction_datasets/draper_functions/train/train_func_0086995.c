gnl_composition_reset (GnlComposition * comp)
{
  GST_DEBUG_OBJECT (comp, "resetting");

  comp->priv->segment_start = GST_CLOCK_TIME_NONE;
  comp->priv->segment_stop = GST_CLOCK_TIME_NONE;

  gst_segment_init (comp->priv->segment, GST_FORMAT_TIME);
  gst_segment_init (comp->priv->outside_segment, GST_FORMAT_TIME);

  if (comp->priv->current)
    g_node_destroy (comp->priv->current);
  comp->priv->current = NULL;

  comp->priv->stackvalid = FALSE;

  if (comp->priv->ghostpad) {
    gnl_object_remove_ghost_pad ((GnlObject *) comp, comp->priv->ghostpad);
    comp->priv->ghostpad = NULL;
    comp->priv->ghosteventprobe = 0;
  }

  if (comp->priv->childseek) {
    gst_event_unref (comp->priv->childseek);
    comp->priv->childseek = NULL;
  }

  reset_childs (comp);

  COMP_FLUSHING_LOCK (comp);
  if (comp->priv->pending_idle)
    g_source_remove (comp->priv->pending_idle);
  comp->priv->pending_idle = 0;
  comp->priv->flushing = FALSE;
  COMP_FLUSHING_UNLOCK (comp);

  comp->priv->update_required = FALSE;

  GST_DEBUG_OBJECT (comp, "Composition now resetted");
}
