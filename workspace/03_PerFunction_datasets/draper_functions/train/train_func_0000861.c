log_in_clicked (GtkWidget *button, gpointer user_data)
{
  BishoPaneOauth *pane = BISHO_PANE_OAUTH (user_data);
  BishoPaneOauthPrivate *priv = pane->priv;
  ServiceInfo *info = BISHO_PANE (pane)->info;
  GError *error = NULL;

  if (oauth_proxy_request_token_async (OAUTH_PROXY (priv->proxy),
                                       priv->request_token_function,
                                       priv->callback,
                                       request_token_cb,
                                       NULL,
                                       pane,
                                       &error)) {
    update_widgets (pane, WORKING);
  } else {
    update_widgets (pane, LOGGED_OUT);

    g_message ("Error from %s: %s", info->name, error->message);
    bisho_pane_set_banner_error (BISHO_PANE (pane), error);
    g_error_free (error);
    return;
  }
}
