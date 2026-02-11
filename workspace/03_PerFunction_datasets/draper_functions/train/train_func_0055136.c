flickr_proxy_is_successful (RestXmlNode *root, GError **error)
{
  RestXmlNode *node;

  g_return_val_if_fail (root, FALSE);

  if (strcmp (root->name, "rsp") != 0) {
    g_set_error (error, FLICKR_PROXY_ERROR, 0,
                 "Unexpected response from Flickr (root node %s)",
                 root->name);
    return FALSE;
  }

  if (strcmp (rest_xml_node_get_attr (root, "stat"), "ok") != 0) {
    node = rest_xml_node_find (root, "err");
    g_set_error_literal (error,FLICKR_PROXY_ERROR,
                         atoi (rest_xml_node_get_attr (node, "code")),
                         rest_xml_node_get_attr (node, "msg"));
    return FALSE;
  }

  return TRUE;
}
