egg_set_desktop_file_internal (const char *desktop_file_path,
                               gboolean set_defaults)
{
  GError *error = NULL;

  G_LOCK (egg_desktop_file);
  if (egg_desktop_file)
    egg_desktop_file_free (egg_desktop_file);

  egg_desktop_file = egg_desktop_file_new (desktop_file_path, &error);
  if (error)
    {
      g_warning ("Could not load desktop file '%s': %s",
		 desktop_file_path, error->message);
      g_error_free (error);
    }

  if (set_defaults && egg_desktop_file != NULL) {

    if (egg_desktop_file->name)
      g_set_application_name (egg_desktop_file->name);
    if (egg_desktop_file->icon)
      {
        if (g_path_is_absolute (egg_desktop_file->icon))
          gtk_window_set_default_icon_from_file (egg_desktop_file->icon, NULL);
        else
          gtk_window_set_default_icon_name (egg_desktop_file->icon);
      }
  }

  G_UNLOCK (egg_desktop_file);
}
