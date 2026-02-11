_set_duration (GESTimelineElement * element, GstClockTime duration)
{
  GList *tmp;
  GESTimeline *timeline;

  GESContainer *container = GES_CONTAINER (element);

  container->children_control_mode = GES_CHILDREN_IGNORE_NOTIFIES;
  for (tmp = container->children; tmp; tmp = g_list_next (tmp)) {
    GESTimelineElement *child = (GESTimelineElement *) tmp->data;

    if (child != container->initiated_move) {

      timeline = GES_TIMELINE_ELEMENT_TIMELINE (child);
      if (timeline == NULL || ges_timeline_trim_object_simple (timeline, child,
              NULL, GES_EDGE_END, _START (child) + duration, TRUE) == FALSE)
        _set_duration0 (GES_TIMELINE_ELEMENT (child), duration);
    }
  }
  container->children_control_mode = GES_CHILDREN_UPDATE;

  return TRUE;
}
