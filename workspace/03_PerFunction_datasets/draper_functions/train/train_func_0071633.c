get_iter_for_profile (GtkTreeModel *model, CdProfile *profile, GtkTreeIter *parent)
{
  const gchar *id;
  gboolean ret;
  GtkTreeIter iter;
  CdProfile *profile_tmp;


  ret = gtk_tree_model_iter_children (model, &iter, parent);
  if (!ret)
    return NULL;


  id = cd_profile_get_id (profile);
  while (ret)
    {
      gtk_tree_model_get (model, &iter,
              GCM_PREFS_COLUMN_PROFILE, &profile_tmp,
              -1);
      if (g_strcmp0 (id, cd_profile_get_id (profile_tmp)) == 0)
        {
          g_object_unref (profile_tmp);
          return gtk_tree_iter_copy (&iter);
        }
      g_object_unref (profile_tmp);
      ret = gtk_tree_model_iter_next (model, &iter);
    }

  return NULL;
}
