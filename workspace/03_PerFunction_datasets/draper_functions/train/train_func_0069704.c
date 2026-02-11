infc_browser_get_subscribe_chat_request(InfcBrowser* browser)
{
  InfcBrowserPrivate* priv;
  InfcBrowserIterGetNodeRequestForeachData data;

  data.result = NULL;

  g_return_val_if_fail(INFC_IS_BROWSER(browser), NULL);
  priv = INFC_BROWSER_PRIVATE(browser);

  if(priv->request_manager != NULL)
  {
    infc_request_manager_foreach_named_request(
      priv->request_manager,
      "subscribe-chat",
      infc_browser_get_chat_request_foreach_func,
      &data
    );
  }

  return data.result;
}
