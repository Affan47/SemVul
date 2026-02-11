gnac_ui_destroy(void)
{
  gnac_properties_destroy();
  gnac_prefs_destroy();
  gnac_profiles_mgr_destroy();

  gnac_file_list_destroy();

  if (G_IS_OBJECT(trayicon)) {
    g_object_unref(trayicon);
    trayicon = NULL;
    if (tooltip_path) {
      g_free(tooltip_path);
      tooltip_path = NULL;
    }
  }

  if (G_IS_OBJECT(gnac_main_builder)) {
    GtkWidget *main_window = gnac_ui_get_widget("main_window");
    if (GTK_IS_WIDGET(main_window)) gtk_widget_destroy(main_window);

    GtkWidget *about_dialog = gnac_ui_get_widget("aboutdialog");
    if (GTK_IS_WIDGET(about_dialog)) gtk_widget_destroy(about_dialog);

    gnac_ui_file_chooser_dispose();
    g_object_unref(gnac_main_builder);
    gnac_main_builder = NULL;
  }

  g_free(status_msg);
}
