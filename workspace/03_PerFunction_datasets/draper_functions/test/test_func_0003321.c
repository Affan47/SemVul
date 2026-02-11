object_active_changed (GnlObject * object, GParamSpec * arg G_GNUC_UNUSED,
    GnlComposition * comp)
{
  GST_DEBUG_OBJECT (object,
      "active flag changed (%d), evaluating pipeline update", object->active);

  if (!comp->priv->can_update) {
    comp->priv->update_required = TRUE;
    return;
  }

  if (comp->priv->current && OBJECT_IN_ACTIVE_SEGMENT (comp, object)) {
    GstClockTime curpos = get_current_position (comp);
    if (curpos == GST_CLOCK_TIME_NONE)
      curpos = comp->priv->segment->start = comp->priv->segment_start;
    update_pipeline (comp, curpos, TRUE, TRUE, TRUE);
  } else
    update_start_stop_duration (comp);
}
