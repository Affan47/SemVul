_edit (GESContainer * container, GList * layers,
    gint new_layer_priority, GESEditMode mode, GESEdge edge, guint64 position)
{
  GList *tmp;
  gboolean ret = TRUE;
  GESLayer *layer;

  if (!G_UNLIKELY (GES_CONTAINER_CHILDREN (container))) {
    GST_WARNING_OBJECT (container, "Trying to edit, but not containing"
        "any TrackElement yet.");
    return FALSE;
  }

  for (tmp = GES_CONTAINER_CHILDREN (container); tmp; tmp = g_list_next (tmp)) {
    if (GES_IS_SOURCE (tmp->data)) {
      ret &= ges_track_element_edit (tmp->data, layers, mode, edge, position);
      break;
    }
  }


  if (new_layer_priority == -1) {
    GST_DEBUG_OBJECT (container, "Not moving new prio %d", new_layer_priority);
  } else {
    gint priority_offset;

    layer = GES_CLIP (container)->priv->layer;
    if (layer == NULL) {
      GST_WARNING_OBJECT (container, "Not in any layer yet, not moving");

      return FALSE;
    }
    priority_offset = new_layer_priority - ges_layer_get_priority (layer);

    ret &= timeline_context_to_layer (layer->timeline, priority_offset);
  }

  return ret;
}
