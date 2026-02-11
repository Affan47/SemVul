gnl_composition_set_update (GnlComposition * comp, gboolean update)
{
  if (G_UNLIKELY (update == comp->priv->can_update))
    return;

  GST_DEBUG_OBJECT (comp, "update:%d [currently %d], update_required:%d",
      update, comp->priv->can_update, comp->priv->update_required);

  COMP_OBJECTS_LOCK (comp);
  comp->priv->can_update = update;

  if (update && comp->priv->update_required) {
    GstClockTime curpos;


    if ((curpos = get_current_position (comp)) == GST_CLOCK_TIME_NONE) {
      if (GST_CLOCK_TIME_IS_VALID (comp->priv->segment_start))
        curpos = comp->priv->segment->start = comp->priv->segment_start;
      else
        curpos = 0;
    }

    COMP_OBJECTS_UNLOCK (comp);


    update_pipeline (comp, curpos, TRUE, TRUE, TRUE);
  } else
    COMP_OBJECTS_UNLOCK (comp);
}
