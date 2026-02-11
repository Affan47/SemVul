_set_duration (GESTimelineElement * element, GstClockTime duration)
{
  GList *tmp;
  GstClockTime last_child_end = 0, new_end;
  GESContainer *container = GES_CONTAINER (element);
  GESGroupPrivate *priv = GES_GROUP (element)->priv;

  if (priv->setting_value == TRUE)

    return GES_TIMELINE_ELEMENT_CLASS (parent_class)->set_duration (element,
        duration);

  if (container->initiated_move == NULL) {
    gboolean expending = (_DURATION (element) < duration);

    new_end = _START (element) + duration;
    container->children_control_mode = GES_CHILDREN_IGNORE_NOTIFIES;
    for (tmp = GES_CONTAINER_CHILDREN (element); tmp; tmp = tmp->next) {
      GESTimelineElement *child = tmp->data;
      GstClockTime n_dur;

      if ((!expending && _END (child) > new_end) ||
          (expending && (_END (child) >= _END (element)))) {
        n_dur = MAX (0, ((gint64) (new_end - _START (child))));
        _set_duration0 (child, n_dur);
      }
    }
    container->children_control_mode = GES_CHILDREN_UPDATE;
  }

  for (tmp = GES_CONTAINER_CHILDREN (element); tmp; tmp = tmp->next) {
    if (_DURATION (tmp->data))
      last_child_end =
          MAX (GES_TIMELINE_ELEMENT_END (tmp->data), last_child_end);
  }

  priv->setting_value = TRUE;
  _set_duration0 (element, last_child_end - _START (element));
  priv->setting_value = FALSE;

  return FALSE;
}
