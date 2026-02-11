gnac_profiles_properties_combo_format_on_changed(GtkComboBox *combo,
                                                 gpointer     user_data)
{
  GtkTreeModel *model = gtk_combo_box_get_model(combo);

  GtkTreeIter iter;
  if (!gtk_combo_box_get_active_iter(combo, &iter)) return;

  FormatModule *format_module;
  gtk_tree_model_get(model, &iter, 1, &format_module, -1);

  gnac_profiles_properties_display_status_message(NULL);

  if (current_format_module && format_module != current_format_module) {
    GtkWidget *properties = current_format_module->funcs.get_widget();
    gtk_widget_hide(properties);
  }

  GtkWidget *text_view =
      gnac_profiles_properties_get_widget("gstreamer_pipeline_text_view");
  gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);

  #ifndef GNOME_ENABLE_DEBUG
    text_view = gnac_profiles_properties_get_widget("gstreamer_pipeline_box");
    gtk_widget_hide(text_view);
  #endif

  GtkLabel *label = GTK_LABEL(
      gnac_profiles_properties_get_widget("format_description_label"));
  gtk_label_set_text(label, format_module->funcs.get_description());
  GtkWidget *widget = format_module->funcs.get_widget();
  gtk_widget_show(widget);
  format_module->funcs.generate_pipeline();
  current_format_module = format_module;
}
