getXMLElement (xmlNodePtr node, const char *tagName)
{
  if (xmlStrcmp (node->name, BAD_CAST (tagName)) == 0)
    return (node);
  node = XML_CHILDREN (node);
  while (node) {
    if (xmlStrcmp (node->name, BAD_CAST (tagName)) == 0) {
      return (node);
    }
    node = node->next;
  }

  return (node);
}
