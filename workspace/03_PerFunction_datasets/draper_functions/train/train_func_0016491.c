inf_text_gtk_view_user_removed(InfTextGtkView* view,
                               InfTextUser* user)
{
  InfTextGtkViewPrivate* priv;
  InfTextGtkViewUser* view_user;

  priv = INF_TEXT_GTK_VIEW_PRIVATE(view);

  if(user == priv->active_user)
  {
    priv->active_user = NULL;
    g_object_notify(G_OBJECT(view), "active-user");
  }
  else
  {
    inf_signal_handlers_disconnect_by_func(
      user,
      G_CALLBACK(inf_text_gtk_view_user_notify_status_cb),
      view
    );

    if(inf_user_get_status(INF_USER(user)) == INF_USER_ACTIVE)
    {
      view_user = inf_text_gtk_view_find_user(view, user);
      g_assert(view_user != NULL);

      inf_text_gtk_view_remove_user(view_user);
    }
  }
}
