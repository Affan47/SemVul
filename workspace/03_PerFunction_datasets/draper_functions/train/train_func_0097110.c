inf_text_gtk_view_user_cursor_blink_timeout_func(gpointer user_data)
{
  InfTextGtkViewUser* view_user;
  InfTextGtkViewPrivate* priv;
  GtkSettings* settings;
  gboolean cursor_blink;
  gint cursor_blink_time;

  view_user = (InfTextGtkViewUser*)user_data;
  priv = INF_TEXT_GTK_VIEW_PRIVATE(view_user->view);

  view_user->cursor_visible = !view_user->cursor_visible;
  inf_text_gtk_view_user_invalidate_user_area(view_user);


  settings = gtk_widget_get_settings(GTK_WIDGET(priv->textview));


  g_object_get(
    G_OBJECT(settings),
    "gtk-cursor-blink", &cursor_blink,
    "gtk-cursor-blink-time", &cursor_blink_time,
    NULL
  );

  if(cursor_blink)
  {
    if(!view_user->cursor_visible)
      cursor_blink_time = cursor_blink_time * 1 / 3;
    else
      cursor_blink_time = cursor_blink_time * 2 / 3;

    view_user->timeout = inf_io_add_timeout(
      priv->io,
      cursor_blink_time,
      inf_text_gtk_view_user_cursor_blink_timeout_func,
      view_user,
      NULL
    );
  }
  else
  {
    view_user->timeout = NULL;
  }
}
