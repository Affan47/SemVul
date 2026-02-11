gnl_composition_finalize (GObject * object)
{
  GnlComposition *comp = GNL_COMPOSITION (object);

  GST_INFO ("finalize");

  COMP_OBJECTS_LOCK (comp);
  g_list_free (comp->priv->objects_start);
  g_list_free (comp->priv->objects_stop);
  if (comp->priv->current)
    g_node_destroy (comp->priv->current);
  g_hash_table_destroy (comp->priv->objects_hash);
  COMP_OBJECTS_UNLOCK (comp);

  g_mutex_free (comp->priv->objects_lock);
  gst_segment_free (comp->priv->segment);
  gst_segment_free (comp->priv->outside_segment);

  g_mutex_free (comp->priv->flushing_lock);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}
