gst_caps_is_equal_fixed (const GstCaps * caps1, const GstCaps * caps2)
{
  GstStructure *struct1, *struct2;
  GstCapsFeatures *features1, *features2;

  g_return_val_if_fail (gst_caps_is_fixed (caps1), FALSE);
  g_return_val_if_fail (gst_caps_is_fixed (caps2), FALSE);

  struct1 = gst_caps_get_structure_unchecked (caps1, 0);
  features1 = gst_caps_get_features_unchecked (caps1, 0);
  if (!features1)
    features1 = GST_CAPS_FEATURES_MEMORY_SYSTEM_MEMORY;
  struct2 = gst_caps_get_structure_unchecked (caps2, 0);
  features2 = gst_caps_get_features_unchecked (caps2, 0);
  if (!features2)
    features2 = GST_CAPS_FEATURES_MEMORY_SYSTEM_MEMORY;

  return gst_structure_is_equal (struct1, struct2) &&
      gst_caps_features_is_equal (features1, features2);
}
