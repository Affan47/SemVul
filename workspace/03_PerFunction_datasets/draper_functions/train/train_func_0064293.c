inf_gtk_browser_view_row_changed_cb(GtkTreeModel* model,
                                    GtkTreePath* path,
                                    GtkTreeIter* iter,
                                    gpointer user_data)
{
  InfGtkBrowserView* view;
  InfGtkBrowserViewPrivate* priv;
  GtkTreeIter parent_iter;
  InfGtkBrowserModelStatus status;
  InfDiscoveryInfo* info;

  view = INF_GTK_BROWSER_VIEW(user_data);
  priv = INF_GTK_BROWSER_VIEW_PRIVATE(view);

  if(gtk_tree_model_iter_parent(model, &parent_iter, iter) == FALSE)
  {
    gtk_tree_model_get(
      model,
      iter,
      INF_GTK_BROWSER_MODEL_COL_STATUS, &status,
      INF_GTK_BROWSER_MODEL_COL_DISCOVERY_INFO, &info,
      -1
    );


    if(status == INF_GTK_BROWSER_MODEL_CONNECTED)
    {
      inf_gtk_browser_view_initial_root_explore(view, path, iter);
    }


    if(info != NULL && status == INF_GTK_BROWSER_MODEL_ERROR)
      priv->info_resolvs = g_slist_remove(priv->info_resolvs, info);
  }
}
