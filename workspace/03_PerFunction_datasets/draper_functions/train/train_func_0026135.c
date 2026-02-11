ges_track_element_dispose (GObject * object)
{
  GESTrackElement *element = GES_TRACK_ELEMENT (object);
  GESTrackElementPrivate *priv = element->priv;

  g_hash_table_destroy (priv->children_props);
  if (priv->bindings_hashtable)
    g_hash_table_destroy (priv->bindings_hashtable);

  if (priv->gnlobject) {
    GstState cstate;

    if (priv->track != NULL) {
      g_error ("%p Still in %p, this means that you forgot"
          " to remove it from the GESTrack it is contained in. You always need"
          " to remove a GESTrackElement from its track before dropping the last"
          " reference\n"
          "This problem may also be caused by a refcounting bug in"
          " the application or GES itself.", object, priv->track);
      gst_element_get_state (priv->gnlobject, &cstate, NULL, 0);
      if (cstate != GST_STATE_NULL)
        gst_element_set_state (priv->gnlobject, GST_STATE_NULL);
    }

    g_object_set_qdata (G_OBJECT (priv->gnlobject),
        GNL_OBJECT_TRACK_ELEMENT_QUARK, NULL);
    gst_object_unref (priv->gnlobject);
    priv->gnlobject = NULL;
  }

  G_OBJECT_CLASS (ges_track_element_parent_class)->dispose (object);
}
