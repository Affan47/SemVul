mxmlFindElement(mxml_node_t *node,
                mxml_node_t *top,
                const char  *name,
		const char  *attr,
		const char  *value,
		int         descend)
{
  const char	*temp;


  if (!node || !top || (!attr && value))
    return (NULL);


  node = mxmlWalkNext(node, top, descend);


  while (node != NULL)
  {


    if (node->type == MXML_ELEMENT &&
        node->value.element.name &&
	(!name || !strcmp(node->value.element.name, name)))
    {


      if (!attr)
        return (node);


      if ((temp = mxmlElementGetAttr(node, attr)) != NULL)
      {


	if (!value || !strcmp(value, temp))
	  return (node);
      }
    }


    if (descend == MXML_DESCEND)
      node = mxmlWalkNext(node, top, MXML_DESCEND);
    else
      node = node->next;
  }

  return (NULL);
}
