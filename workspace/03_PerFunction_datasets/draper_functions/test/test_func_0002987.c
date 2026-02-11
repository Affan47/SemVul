gnac_profiles_properties_show(gpointer     profile,
                              const gchar *title,
                              GCallback    call_back)
{
  gnac_profiles_properties_reset();

  GtkWidget *widget = gnac_profiles_properties_get_widget("save-button");

  g_signal_connect(G_OBJECT(widget), "clicked",
      G_CALLBACK(gnac_profiles_properties_on_save), call_back);

  widget = gnac_profiles_properties_get_widget("window1");
  gtk_window_set_title(GTK_WINDOW(widget), title);

  GtkWidget *format_combo_box =
      gnac_profiles_properties_get_widget("format_combo_box");

  if (!profile) {
    gtk_widget_show(widget);
    gtk_combo_box_set_active(GTK_COMBO_BOX(format_combo_box), 0);
    return;
  }

  AudioProfileGeneric *generic = AUDIO_PROFILE_GET_GENERIC(profile);
  const gchar *format_id = generic->format_id;
  if (!format_id) return;

  FormatModule *format_module = g_hash_table_lookup(formats, format_id);
  if (!format_module) {
    libgnac_warning(_("Format not supported"));
    return;
  }

  GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(format_combo_box));
  gnac_profiles_properties_name_description_set_text(generic->name,
      generic->description);
  format_module->funcs.set_fields(profile);

  GtkTreeIter iter;
  GtkTreePath *path = gtk_tree_row_reference_get_path(format_module->tree_ref);
  gtk_tree_model_get_iter(model, &iter, path);
  gtk_tree_path_free(path);
  gtk_combo_box_set_active_iter(GTK_COMBO_BOX(format_combo_box), &iter);
  format_module->funcs.generate_pipeline();

  gtk_widget_show(widget);
}
