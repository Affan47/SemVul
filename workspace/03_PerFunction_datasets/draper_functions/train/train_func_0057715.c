gst_caps_merge_structure (GstCaps * caps, GstStructure * structure)
{
  GstStructure *structure1;
  GstCapsFeatures *features1;
  int i;
  gboolean unique = TRUE;

  g_return_val_if_fail (GST_IS_CAPS (caps), NULL);

  if (G_UNLIKELY (structure == NULL))
    return caps;


  for (i = GST_CAPS_LEN (caps) - 1; i >= 0; i--) {
    structure1 = gst_caps_get_structure_unchecked (caps, i);
    features1 = gst_caps_get_features_unchecked (caps, i);
    if (!features1)
      features1 = GST_CAPS_FEATURES_MEMORY_SYSTEM_MEMORY;


    if (gst_caps_features_is_equal (features1,
            GST_CAPS_FEATURES_MEMORY_SYSTEM_MEMORY)
        && gst_structure_is_subset (structure, structure1)) {
      unique = FALSE;
      break;
    }
  }
  if (unique) {
    caps = gst_caps_make_writable (caps);
    gst_caps_append_structure_unchecked (caps, structure, NULL);
  } else {
    gst_structure_free (structure);
  }
  return caps;
}
