refine_start_stop_in_region_above_priority (GnlComposition * composition,
    GstClockTime timestamp, GstClockTime start,
    GstClockTime stop,
    GstClockTime * rstart, GstClockTime * rstop, guint32 priority)
{
  GList *tmp;
  GnlObject *object;
  GstClockTime nstart = start, nstop = stop;

  GST_DEBUG_OBJECT (composition,
      "timestamp:%" GST_TIME_FORMAT " start: %" GST_TIME_FORMAT " stop: %"
      GST_TIME_FORMAT " priority:%u", GST_TIME_ARGS (timestamp),
      GST_TIME_ARGS (start), GST_TIME_ARGS (stop), priority);

  for (tmp = composition->priv->objects_start; tmp; tmp = tmp->next) {
    object = (GnlObject *) tmp->data;

    GST_LOG_OBJECT (object, "START %" GST_TIME_FORMAT "--%" GST_TIME_FORMAT,
        GST_TIME_ARGS (object->start), GST_TIME_ARGS (object->stop));

    if ((object->priority >= priority) || (!object->active))
      continue;

    if (object->start <= timestamp)
      continue;

    if (object->start >= nstop)
      continue;

    nstop = object->start;

    GST_DEBUG_OBJECT (composition,
        "START Found %s [prio:%u] at %" GST_TIME_FORMAT,
        GST_OBJECT_NAME (object), object->priority,
        GST_TIME_ARGS (object->start));

    break;
  }

  for (tmp = composition->priv->objects_stop; tmp; tmp = tmp->next) {
    object = (GnlObject *) tmp->data;

    GST_LOG_OBJECT (object, "STOP %" GST_TIME_FORMAT "--%" GST_TIME_FORMAT,
        GST_TIME_ARGS (object->start), GST_TIME_ARGS (object->stop));

    if ((object->priority >= priority) || (!object->active))
      continue;

    if (object->stop >= timestamp)
      continue;

    if (object->stop <= nstart)
      continue;

    nstart = object->stop;

    GST_DEBUG_OBJECT (composition,
        "STOP Found %s [prio:%u] at %" GST_TIME_FORMAT,
        GST_OBJECT_NAME (object), object->priority,
        GST_TIME_ARGS (object->start));

    break;
  }

  if (*rstart)
    *rstart = nstart;

  if (*rstop)
    *rstop = nstop;
}
