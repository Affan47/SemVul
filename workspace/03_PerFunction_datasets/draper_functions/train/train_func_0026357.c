infc_browser_add_note(InfcBrowser* browser,
                      const InfcBrowserIter* parent,
                      const gchar* name,
                      const InfcNotePlugin* plugin,
                      gboolean initial_subscribe)
{
  InfcBrowserPrivate* priv;
  InfcBrowserNode* node;
  InfcRequest* request;
  xmlNodePtr xml;

  g_return_val_if_fail(INFC_IS_BROWSER(browser), NULL);
  infc_browser_return_val_if_iter_fail(browser, parent, NULL);
  g_return_val_if_fail(name != NULL, NULL);
  g_return_val_if_fail(plugin != NULL, NULL);

  node = (InfcBrowserNode*)parent->node;
  infc_browser_return_val_if_subdir_fail(node, NULL);
  g_return_val_if_fail(node->shared.subdir.explored == TRUE, NULL);

  priv = INFC_BROWSER_PRIVATE(browser);
  g_return_val_if_fail(priv->connection != NULL, NULL);
  g_return_val_if_fail(priv->status == INFC_BROWSER_CONNECTED, NULL);

  request = infc_request_manager_add_request(
    priv->request_manager,
    INFC_TYPE_NODE_REQUEST,
    "add-node",
    "node-id", parent->node_id,
    NULL
  );

  xml = infc_browser_request_to_xml(request);
  inf_xml_util_set_attribute_uint(xml, "parent", node->id);
  inf_xml_util_set_attribute(xml, "type", plugin->note_type);
  inf_xml_util_set_attribute(xml, "name", name);

  if(initial_subscribe != FALSE)
    xmlNewChild(xml, NULL, (const xmlChar*)"subscribe", NULL);

  inf_communication_group_send_message(
    INF_COMMUNICATION_GROUP(priv->group),
    priv->connection,
    xml
  );

  return INFC_NODE_REQUEST(request);
}
