inf_text_gtk_buffer_set_active_user(InfTextGtkBuffer* buffer,
                                    InfTextUser* user)
{
  InfTextGtkBufferPrivate* priv;

  g_return_if_fail(INF_TEXT_GTK_IS_BUFFER(buffer));
  g_return_if_fail(user == NULL || INF_TEXT_IS_USER(user));

  g_return_if_fail(
    user == NULL ||
    (inf_user_get_flags(INF_USER(user)) & INF_USER_LOCAL) != 0
  );

  g_return_if_fail(
    user == NULL ||
    inf_user_get_status(INF_USER(user)) != INF_USER_UNAVAILABLE
  );

  priv = INF_TEXT_GTK_BUFFER_PRIVATE(buffer);

  if(priv->active_user != NULL)
  {
    inf_signal_handlers_disconnect_by_func(
      G_OBJECT(priv->active_user),
      G_CALLBACK(inf_text_gtk_buffer_active_user_notify_status_cb),
      buffer
    );

    inf_signal_handlers_disconnect_by_func(
      G_OBJECT(priv->active_user),
      G_CALLBACK(inf_text_gtk_buffer_active_user_selection_changed_cb),
      buffer
    );

    g_object_unref(G_OBJECT(priv->active_user));
  }

  priv->active_user = user;

  if(user != NULL)
  {


    g_object_ref(G_OBJECT(user));

    g_signal_connect(
      G_OBJECT(user),
      "notify::status",
      G_CALLBACK(inf_text_gtk_buffer_active_user_notify_status_cb),
      buffer
    );

    g_signal_connect(
      G_OBJECT(user),
      "selection-changed",
      G_CALLBACK(inf_text_gtk_buffer_active_user_selection_changed_cb),
      buffer
    );
  }

  g_object_notify(G_OBJECT(buffer), "active-user");
}
