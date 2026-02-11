on_form_submit (WebKitDOMNode *element, WebKitDOMEvent *event, gpointer user_data)
{
  GoaOAuth2Provider *provider = GOA_OAUTH2_PROVIDER (user_data);
  GoaOAuth2ProviderPrivate *priv = provider->priv;

  if (priv->password_node == NULL)
    return;

  priv->password = webkit_dom_html_input_element_get_value (priv->password_node);
  priv->password_node = NULL;
}
