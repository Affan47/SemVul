inf_gtk_browser_view_row_expanded(GtkTreeView* tree_view,
                                  GtkTreeIter* iter,
                                  GtkTreePath* path)
{
  GtkTreeModel* model;
  InfcBrowser* browser;
  InfcBrowserIter* browser_iter;

  model = gtk_tree_view_get_model(tree_view);

  gtk_tree_model_get(
    model,
    iter,
    INF_GTK_BROWSER_MODEL_COL_BROWSER, &browser,
    INF_GTK_BROWSER_MODEL_COL_NODE, &browser_iter,
    -1
  );

  g_assert(browser != NULL);


  if(infc_browser_iter_get_child(browser, browser_iter))
  {
    do
    {
      if(infc_browser_iter_is_subdirectory(browser, browser_iter) == TRUE &&
         infc_browser_iter_get_explored(browser, browser_iter) == FALSE &&
         infc_browser_iter_get_explore_request(browser, browser_iter) == NULL)
      {
        infc_browser_iter_explore(browser, browser_iter);
      }
    } while(infc_browser_iter_get_next(browser, browser_iter));
  }

  infc_browser_iter_free(browser_iter);
  g_object_unref(G_OBJECT(browser));

  if(GTK_TREE_VIEW_CLASS(parent_class)->row_expanded != NULL)
    GTK_TREE_VIEW_CLASS(parent_class)->row_expanded(tree_view, iter, path);
}
