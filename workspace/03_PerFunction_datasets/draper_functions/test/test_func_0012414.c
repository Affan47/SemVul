gst_caps_features_add_id (GstCapsFeatures * features, GQuark feature)
{
  g_return_if_fail (features != NULL);
  g_return_if_fail (IS_MUTABLE (features));
  g_return_if_fail (feature != 0);
  g_return_if_fail (!features->is_any);

  if (!gst_caps_feature_name_is_valid (g_quark_to_string (feature))) {
    g_warning ("Invalid caps feature name: %s", g_quark_to_string (feature));
    return;
  }


  if (features->array->len > 0
      && gst_caps_features_contains_id (features, feature))
    return;

  g_array_append_val (features->array, feature);
}
