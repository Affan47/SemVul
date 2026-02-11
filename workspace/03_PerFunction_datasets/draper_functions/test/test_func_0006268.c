bisho_pane_oauth_continue_auth (BishoPane *_pane, GHashTable *params)
{
  BishoPaneOauth *pane = BISHO_PANE_OAUTH (_pane);
  BishoPaneOauthPrivate *priv = pane->priv;
  ServiceInfo *info = BISHO_PANE (pane)->info;
  GError *error = NULL;
  const char *verifier;


  if (oauth_proxy_is_oauth10a (OAUTH_PROXY (priv->proxy))) {

    if (strcmp (priv->callback, "oob") == 0) {
      verifier = gtk_entry_get_text (GTK_ENTRY (priv->pin_entry));
      gtk_widget_hide (priv->pin_label);
      gtk_widget_hide (priv->pin_entry);
    } else {
      verifier = g_hash_table_lookup (params, "oauth_verifier");
    }
  } else {
    verifier = NULL;
  }

  if (oauth_proxy_access_token_async (OAUTH_PROXY (priv->proxy),
                                      priv->access_token_function,
                                      verifier,
                                      access_token_cb,
                                      NULL,
                                      pane,
                                      &error)) {
    update_widgets (pane, WORKING);
  } else {
    update_widgets (pane, LOGGED_OUT);
    g_message ("Error from %s: %s", info->name, error->message);
    bisho_pane_set_banner_error (BISHO_PANE (pane), error);
    return;
  }
}
