infc_browser_handle_explore_end(InfcBrowser* browser,
                                InfXmlConnection* connection,
                                xmlNodePtr xml,
                                GError** error)
{
  InfcBrowserPrivate* priv;
  InfcRequest* request;
  gboolean result;

  priv = INFC_BROWSER_PRIVATE(browser);


  request = infc_request_manager_get_request_by_xml_required(
    priv->request_manager,
    "explore-node",
    xml,
    error
  );

  if(request == NULL) return FALSE;
  g_assert(INFC_IS_EXPLORE_REQUEST(request));

  result = infc_explore_request_finished(
    INFC_EXPLORE_REQUEST(request),
    error
  );

  infc_request_manager_remove_request(priv->request_manager, request);
  return result;
}
