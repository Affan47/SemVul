layout_callback (gpointer user_data)
{
  ExoIconView *icon_view = EXO_ICON_VIEW (user_data);

  GDK_THREADS_ENTER ();
  exo_icon_view_layout (icon_view);
  GDK_THREADS_LEAVE();

  return FALSE;
}
