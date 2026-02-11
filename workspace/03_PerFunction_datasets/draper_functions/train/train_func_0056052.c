exo_icon_view_search_timeout (gpointer user_data)
{
  ExoIconView *icon_view = EXO_ICON_VIEW (user_data);

  GDK_THREADS_ENTER ();
  exo_icon_view_search_dialog_hide (icon_view->priv->search_window, icon_view);
  GDK_THREADS_LEAVE ();

  return FALSE;
}
