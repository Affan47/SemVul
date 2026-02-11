load_keyfile (GESFormatter * keyfile_formatter, GESTimeline * timeline)
{
  GKeyFile *kf;
  GError *error = NULL;
  gboolean ret = TRUE;
  gchar **groups;
  gsize n_groups, i;
  GESTimelineLayer *cur_layer = NULL;
  gchar *data;
  gsize length;

  kf = g_key_file_new ();
  data = ges_formatter_get_data (keyfile_formatter, &length);
  if (!g_key_file_load_from_data (kf, data, length, G_KEY_FILE_NONE, &error)) {
    ret = FALSE;
    GST_ERROR (error->message);
    GST_INFO (data);
    goto free_kf;
  }

  if (!(groups = g_key_file_get_groups (kf, &n_groups))) {
    goto free_kf;
  }

  for (i = 0; i < n_groups; i++) {
    gchar *group = groups[i];

    if (g_str_has_prefix (group, "Track")) {
      if (!create_track (kf, group, timeline)) {
        GST_ERROR ("couldn't create object for %s", group);
        ret = FALSE;
        break;
      }
    }

    else if (g_str_has_prefix (group, "Layer")) {
      if (!(cur_layer = create_layer (kf, group, timeline))) {
        GST_ERROR ("couldn't create object for %s", group);
        ret = FALSE;
        break;
      }
    }

    else if (g_str_has_prefix (group, "Object")) {
      if (!cur_layer) {
        GST_ERROR ("Group %s occurs outside of Layer", group);
        ret = FALSE;
        break;
      }

      if (!create_object (kf, group, cur_layer)) {
        GST_ERROR ("couldn't create object for %s", group);
        ret = FALSE;
        break;
      }
    }

    else if (g_str_equal (group, "General")) {
      continue;
    }

    else {
      GST_ERROR ("Unrecognized group name %s", group);
      ret = FALSE;
      break;
    }
  }

  g_strfreev (groups);

free_kf:
  g_key_file_free (kf);
  return ret;
}
