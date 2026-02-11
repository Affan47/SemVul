gst_discoverer_dispose (GObject * obj)
{
  GstDiscoverer *dc = (GstDiscoverer *) obj;

  GST_DEBUG_OBJECT (dc, "Disposing");

  discoverer_reset (dc);

  if (G_LIKELY (dc->priv->pipeline)) {

    DISCONNECT_SIGNAL (dc->priv->uridecodebin, dc->priv->pad_added_id);
    DISCONNECT_SIGNAL (dc->priv->uridecodebin, dc->priv->pad_remove_id);
    DISCONNECT_SIGNAL (dc->priv->uridecodebin, dc->priv->source_chg_id);
    DISCONNECT_SIGNAL (dc->priv->uridecodebin, dc->priv->element_added_id);
    DISCONNECT_SIGNAL (dc->priv->bus, dc->priv->bus_cb_id);


    gst_object_unref (dc->priv->pipeline);
    gst_object_unref (dc->priv->bus);

    dc->priv->pipeline = NULL;
    dc->priv->uridecodebin = NULL;
    dc->priv->bus = NULL;
  }

  gst_discoverer_stop (dc);

  if (dc->priv->seeking_query) {
    gst_query_unref (dc->priv->seeking_query);
    dc->priv->seeking_query = NULL;
  }

  G_OBJECT_CLASS (gst_discoverer_parent_class)->dispose (obj);
}
