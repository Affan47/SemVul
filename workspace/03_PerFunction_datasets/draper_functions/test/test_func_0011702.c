exo_icon_view_search_preedit_changed (GtkIMContext *im_context,
                                      ExoIconView  *icon_view)
{
  icon_view->priv->search_imcontext_changed = TRUE;


  if (G_LIKELY (icon_view->priv->search_timeout_id != 0))
    {
      g_source_remove (icon_view->priv->search_timeout_id);
      icon_view->priv->search_timeout_id = g_timeout_add_full (G_PRIORITY_LOW, EXO_ICON_VIEW_SEARCH_DIALOG_TIMEOUT,
                                                               exo_icon_view_search_timeout, icon_view,
                                                               exo_icon_view_search_timeout_destroy);
    }
}
