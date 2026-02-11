_gtr_recent_add (GtrWindow * window, GFile * location, gchar * project_id)
{
  GtkRecentData *recent_data;
  gchar *uri;
  gchar *path;
  gchar *display_name;

  uri = g_file_get_uri (location);
  path = g_file_get_path (location);
  display_name = gtr_utils_reduce_path ((const gchar *) path);

  recent_data = g_slice_new (GtkRecentData);

  recent_data->display_name = display_name;
  recent_data->description = NULL;
  recent_data->mime_type = "text/x-gettext-translation";
  recent_data->app_name = (gchar *) g_get_application_name ();
  recent_data->app_exec = g_strjoin (" ", g_get_prgname (), "%u", NULL);
  recent_data->groups = NULL;
  recent_data->is_private = FALSE;

  if (!gtk_recent_manager_add_full (window->priv->recent_manager,
                                    uri, recent_data))
    {
      g_warning ("Unable to add '%s' to the list of recently used documents",
                 uri);
    }

  g_free (uri);
  g_free (path);
  g_free (display_name);
  g_free (recent_data->app_exec);
  g_slice_free (GtkRecentData, recent_data);
}
