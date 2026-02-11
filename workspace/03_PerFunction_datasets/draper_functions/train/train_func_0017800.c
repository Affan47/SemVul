gtr_po_parse_files_from_dialog (GtkWidget * dialog, GtrWindow * window)
{
  GSList *po_files, *l;
  GSList *locations = NULL;
  GFile *file, *parent;
  gchar *uri;

  po_files = gtk_file_chooser_get_uris (GTK_FILE_CHOOSER (dialog));
  for (l = po_files; l != NULL; l = g_slist_next (l))
    {
      GFile *file;

      file = g_file_new_for_uri (l->data);
      locations = g_slist_prepend (locations, file);
    }


  file = g_file_new_for_uri (po_files->data);
  g_slist_free_full (po_files, g_free);

  parent = g_file_get_parent (file);
  g_object_unref (file);

  uri = g_file_get_uri (parent);
  g_object_unref (parent);
  _gtr_application_set_last_dir (GTR_APP, uri);

  g_free (uri);


  load_file_list (window, (const GSList *) locations);
  g_slist_free_full (locations, g_object_unref);


  gtk_widget_destroy (dialog);
}
