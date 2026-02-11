infc_browser_handle_remove_node(InfcBrowser* browser,
                                InfXmlConnection* connection,
                                xmlNodePtr xml,
                                GError** error)
{
  InfcBrowserPrivate* priv;
  InfcBrowserNode* node;
  InfcRequest* request;
  InfcBrowserIter iter;

  priv = INFC_BROWSER_PRIVATE(browser);
  node = infc_browser_get_node_from_xml(browser, xml, "id", error);
  if(node == NULL) return FALSE;

  request = infc_request_manager_get_request_by_xml(
    priv->request_manager,
    "remove-node",
    xml,
    NULL
  );

  if(request != NULL)
  {
    g_assert(INFC_IS_NODE_REQUEST(request));
    iter.node_id = node->id;
    iter.node = node;
    infc_node_request_finished(INFC_NODE_REQUEST(request), &iter);
    infc_request_manager_remove_request(priv->request_manager, request);
  }


  if(infc_browser_node_remove(browser, node, error) == FALSE)
    return FALSE;

  return TRUE;
}
