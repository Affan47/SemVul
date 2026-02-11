gtr_window_get_all_views (GtrWindow * window,
                          gboolean original, gboolean translated)
{
  gint numtabs;
  gint i;
  GList *views = NULL;
  GtkWidget *tab;

  g_return_val_if_fail (GTR_IS_WINDOW (window), NULL);

  numtabs = gtk_notebook_get_n_pages (GTK_NOTEBOOK (window->priv->notebook));
  i = numtabs - 1;

  while (i >= 0 && numtabs != 0)
    {
      tab = gtk_notebook_get_nth_page (GTK_NOTEBOOK (window->priv->notebook),
                                       i);
      views =
        g_list_concat (views,
                       gtr_tab_get_all_views (GTR_TAB (tab), original,
                                              translated));
      i--;
    }

  return views;
}
