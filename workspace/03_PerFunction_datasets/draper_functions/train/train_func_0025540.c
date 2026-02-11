gnac_profiles_mgr_on_edit_profile(GtkWidget *widget,
                                  gpointer   data)
{
  GList *selected = gnac_profiles_mgr_get_selected_rows();
  if (!selected) return;

  GtkTreeRowReference *reference = (GtkTreeRowReference *) selected->data;

  AudioProfileGeneric *old_profile;
  gnac_profiles_mgr_get(reference, COL_PROFILE, &old_profile);
  AudioProfileGeneric *old_generic = old_profile->generic;

  AudioProfileGeneric *profile = (AudioProfileGeneric *) data;
  AudioProfileGeneric *generic = profile->generic;

  if (!gnac_utils_str_equal(generic->name, old_generic->name)) {
    gnac_profiles_mgr_delete_profile_file(old_generic->name);
  }

  gchar *formatted_name = gnac_profiles_properties_filter_text_for_display(
      generic->name, MAX_NAME_DISPLAY_SIZE);
  gnac_profiles_mgr_set(reference,
      COL_NAME, formatted_name,
      COL_FORMAT, generic->format_name,
      COL_EXTENSION, generic->extension,
      COL_PROFILE, profile,
      -1);

  g_free(formatted_name);
  gnac_profiles_properties_free_audio_profile(old_profile);
  g_list_free_full(selected, (GDestroyNotify) gtk_tree_row_reference_free);

  gnac_profiles_mgr_display_status_message(NULL, NULL);

  gnac_profiles_mgr_on_treeselection_changed();
}
