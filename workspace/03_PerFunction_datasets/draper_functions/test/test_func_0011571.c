stp_mxmlNewText(stp_mxml_node_t *parent,
            int         whitespace,
	    const char  *string)
{
  stp_mxml_node_t	*node;


  if (!parent || !string)
    return (NULL);


  if ((node = mxml_new(parent, STP_MXML_TEXT)) != NULL)
  {
    node->value.text.whitespace = whitespace;
    node->value.text.string     = strdup(string);
  }

  return (node);
}
