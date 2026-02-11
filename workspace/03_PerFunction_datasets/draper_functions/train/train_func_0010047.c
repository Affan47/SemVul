ges_track_element_get_child_property (GESTrackElement * object,
    const gchar * property_name, GValue * value)
{
  GParamSpec *pspec;
  GstElement *element;

  g_return_val_if_fail (GES_IS_TRACK_ELEMENT (object), FALSE);

  if (!ges_track_element_lookup_child (object, property_name, &element, &pspec))
    goto not_found;

  if (G_VALUE_TYPE (value) == G_TYPE_INVALID)
    g_value_init (value, pspec->value_type);

  g_object_get_property (G_OBJECT (element), pspec->name, value);

  gst_object_unref (element);
  g_param_spec_unref (pspec);

  return TRUE;

not_found:
  {
    GST_WARNING_OBJECT (object, "The %s property doesn't exist", property_name);

    return FALSE;
  }
}
