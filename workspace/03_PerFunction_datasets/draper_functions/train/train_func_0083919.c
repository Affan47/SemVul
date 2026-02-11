inf_text_gtk_viewport_set_user_table(InfTextGtkViewport* viewport,
                                     InfUserTable* user_table)
{
  InfTextGtkViewportPrivate* priv;
  priv = INF_TEXT_GTK_VIEWPORT_PRIVATE(viewport);

  if(priv->user_table != NULL)
  {
    inf_signal_handlers_disconnect_by_func(
      G_OBJECT(priv->user_table),
      G_CALLBACK(inf_text_gtk_viewport_add_user_cb),
      viewport
    );

    inf_signal_handlers_disconnect_by_func(
      G_OBJECT(priv->user_table),
      G_CALLBACK(inf_text_gtk_viewport_remove_user_cb),
      viewport
    );

    inf_user_table_foreach_user(
      priv->user_table,
      inf_text_gtk_viewport_set_user_table_foreach_old_user_func,
      viewport
    );

    g_object_unref(priv->user_table);
  }

  priv->user_table = user_table;

  if(user_table != NULL)
  {
    g_object_ref(user_table);

    g_signal_connect(
      G_OBJECT(user_table),
      "add-user",
      G_CALLBACK(inf_text_gtk_viewport_add_user_cb),
      viewport
    );

    g_signal_connect(
      G_OBJECT(user_table),
      "remove-user",
      G_CALLBACK(inf_text_gtk_viewport_remove_user_cb),
      viewport
    );

    inf_user_table_foreach_user(
      user_table,
      inf_text_gtk_viewport_set_user_table_foreach_new_user_func,
      viewport
    );
  }

  g_object_notify(G_OBJECT(viewport), "user-table");
}
