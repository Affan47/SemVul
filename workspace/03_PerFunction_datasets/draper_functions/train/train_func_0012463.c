rest_xml_node_set_content (RestXmlNode *node, const char *value)
{
  g_return_if_fail (node && value && *value);

  g_free (node->content);
  node->content = g_markup_escape_text (value, -1);
}
