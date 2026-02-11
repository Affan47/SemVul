gnac_profiles_mgr_get_selected_uris(void)
{
  GList *selected = gnac_profiles_mgr_get_selected_rows();
  if (!selected) return NULL;

  GtkTreeRowReference *reference = (GtkTreeRowReference *) selected->data;
  gchar **uris = g_malloc((g_list_length(selected)+1) * sizeof(gchar *));

  guint  i;
  GList *temp;

  for (i = 0, temp = selected; temp; temp = g_list_next(temp), i++) {
    AudioProfileGeneric *profile;
    gnac_profiles_mgr_get(reference, COL_PROFILE, &profile);
    profile = profile->generic;
    gchar *path = g_strconcat(GNAC_SAVED_PROFILES_URL_WITH_EXT(profile->name),
        NULL);
    GFile *file = g_file_new_for_path(path);
    uris[i] = g_file_get_uri(file);

    g_free(path);
  }

  uris[i] = NULL;

  g_list_free_full(selected, (GDestroyNotify) gtk_tree_row_reference_free);

  return uris;
}
