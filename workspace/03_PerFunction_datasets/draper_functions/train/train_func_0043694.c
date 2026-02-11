_ges_track_element_get_layer_priority (GESTrackElement * element)
{
  if (_PRIORITY (element) < LAYER_HEIGHT + MIN_GNL_PRIO)
    return 0;

  return (_PRIORITY (element) - MIN_GNL_PRIO) / LAYER_HEIGHT;
}
