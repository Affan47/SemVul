xmlbuilder_end_element(const xmlChar * element_name, void *userData)
{

  struct XmlNodeHolder *holder = (struct XmlNodeHolder *) userData;
  xmlNodePtr parent = NULL;

  if (holder == NULL)
    return;
  parent = holder->node;
  if (parent == NULL)
    return;

  holder->node = parent->parent;

  return;
}
