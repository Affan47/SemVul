gst_preset_default_get_preset_names (GstPreset * preset)
{
  GKeyFile *presets;
  gsize i, num_groups;
  gchar **groups;


  if (!(presets = preset_get_keyfile (preset)))
    goto no_presets;


  if (!(groups = g_key_file_get_groups (presets, &num_groups)))
    goto no_groups;


  for (i = 0; i < num_groups; i++) {
    if (groups[i][0] == '_') {

      g_free (groups[i]);

      num_groups--;

      groups[i] = groups[num_groups];
      groups[num_groups] = NULL;
    }
  }

  g_qsort_with_data (groups, num_groups, sizeof (gchar *),
      (GCompareDataFunc) strcmp, NULL);

  return groups;


no_presets:
  {
    GST_WARNING_OBJECT (preset, "Could not load presets");
    return NULL;
  }
no_groups:
  {
    GST_WARNING_OBJECT (preset, "Could not find preset groups");
    return NULL;
  }
}
