_add_pending_bindings (GESBaseXmlFormatterPrivate * priv, GList * bindings,
    GESClip * clip)
{
  GList *tmpbinding;

  for (tmpbinding = bindings; tmpbinding; tmpbinding = tmpbinding->next) {
    PendingBinding *pbinding = tmpbinding->data;
    GESTrackElement *element =
        _get_element_by_track_id (priv, pbinding->track_id, clip);
    if (element)
      ges_track_element_set_control_source (element,
          pbinding->source, pbinding->propname, pbinding->binding_type);
  }
}
