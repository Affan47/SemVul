audioev_filename_browse_cb (GtkWidget *b,
                            gpointer data)
{

  GmPreferencesWindow *pw = NULL;

  GtkTreeModel *model = NULL;
  GtkTreeSelection *selection = NULL;
  GtkTreeIter iter;

  gchar *filename = NULL;
  gchar *conf_key = NULL;
  gchar *sound_event = NULL;

  g_return_if_fail (data != NULL);
  pw = gm_pw_get_pw (GTK_WIDGET (data));

  selection =
    gtk_tree_view_get_selection (GTK_TREE_VIEW (pw->sound_events_list));

  if (gtk_tree_selection_get_selected (selection, &model, &iter)) {

    gtk_tree_model_get (GTK_TREE_MODEL (model), &iter,
      2, &conf_key, -1);

    if (conf_key) {
      filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (b));
      if (filename) {
        sound_event = gm_conf_get_string (conf_key);

        if (!sound_event || g_strcmp0 (filename, sound_event))
          gm_conf_set_string (conf_key, (gchar *) filename);

        g_free (filename);
      }

      g_free (conf_key);
      g_free (sound_event);
    }
  }
}
