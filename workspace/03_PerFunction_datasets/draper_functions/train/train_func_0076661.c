inf_text_gtk_view_remove_user(InfTextGtkViewUser* view_user)
{
  InfTextGtkViewPrivate* priv;
  priv = INF_TEXT_GTK_VIEW_PRIVATE(view_user->view);

  inf_signal_handlers_disconnect_by_func(
    view_user->user,
    G_CALLBACK(inf_text_gtk_view_user_selection_changed_cb),
    view_user
  );

  inf_signal_handlers_disconnect_by_func(
    view_user->user,
    G_CALLBACK(inf_text_gtk_view_user_notify_hue_cb),
    view_user
  );

  if(view_user->timeout != NULL)
    inf_io_remove_timeout(priv->io, view_user->timeout);

  if(view_user->revalidate_idle != 0)
    g_source_remove(view_user->revalidate_idle);

  inf_text_gtk_view_user_invalidate_user_area(view_user);

  priv->users = g_slist_remove(priv->users, view_user);
  g_slice_free(InfTextGtkViewUser, view_user);
}
