active_toggled_cb (GtkCellRendererToggle *cell_renderer,
                   gchar *path_str, GtrPreferencesDialog *dlg)
{
  GtkTreeIter iter, first;
  GtkTreePath *path;
  GtkTreeModel *model;
  GtrProfile *active_profile;

  path = gtk_tree_path_new_from_string (path_str);

  model = gtk_tree_view_get_model (GTK_TREE_VIEW (dlg->priv->profile_treeview));
  g_return_if_fail (model != NULL);

  gtk_tree_model_get_iter (model, &iter, path);

  gtk_tree_model_get (model, &iter, PROFILE_COLUMN, &active_profile, -1);

  if (active_profile != NULL)
    {
      GtrProfileManager *prof_manager;

      prof_manager = gtr_profile_manager_get_default ();

      if (gtr_profile_manager_get_active_profile (prof_manager) != active_profile)
        {
          gtr_profile_manager_set_active_profile (prof_manager, active_profile);

          gtk_tree_model_get_iter_first (model, &first);

          do
          {
            gtk_list_store_set (GTK_LIST_STORE (model),
                                &first,
                                ACTIVE_PROFILE_COLUMN, FALSE,
                                -1);
          } while (gtk_tree_model_iter_next (model, &first));

          gtk_list_store_set (GTK_LIST_STORE (model),
                              &iter,
                              ACTIVE_PROFILE_COLUMN, TRUE,
                              -1);
        }

      g_object_unref (prof_manager);
    }

  gtk_tree_path_free (path);
}
