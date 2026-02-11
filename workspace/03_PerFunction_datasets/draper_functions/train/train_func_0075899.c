gui_load_theme(const char *directory, const char *theme_name)
{
  GtkCssProvider *css_provider;
  GError *error = NULL;
  char buf[strlen(directory) + strlen(theme_name) + 32];

  fc_snprintf(buf, sizeof(buf), "%s/%s/gtk-3.0/gtk.css", directory,
              theme_name);
  css_provider = gtk_css_provider_new();
  gtk_css_provider_load_from_file(css_provider, g_file_new_for_path(buf), &error);
  if (error) {
    g_warning("%s\n", error->message);
    return;
  }
  gtk_style_context_add_provider_for_screen(
      gtk_widget_get_screen(toplevel),
      GTK_STYLE_PROVIDER(css_provider),
      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}
