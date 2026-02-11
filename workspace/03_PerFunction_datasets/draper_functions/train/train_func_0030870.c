ges_timeline_element_set_timeline (GESTimelineElement * self,
    GESTimeline * timeline)
{
  g_return_val_if_fail (GES_IS_TIMELINE_ELEMENT (self), FALSE);
  g_return_val_if_fail (timeline == NULL || GES_IS_TIMELINE (timeline), FALSE);

  GST_DEBUG_OBJECT (self, "set timeline to %" GST_PTR_FORMAT, timeline);

  if (timeline != NULL && G_UNLIKELY (self->timeline != NULL))
    goto had_timeline;

  self->timeline = timeline;

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_TIMELINE]);
  return TRUE;


had_timeline:
  {
    GST_DEBUG_OBJECT (self, "set timeline failed, object already had a "
        "timeline");
    return FALSE;
  }
}
