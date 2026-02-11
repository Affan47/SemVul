stp_escp2_set_media_size(stp_vars_t *v, const stp_vars_t *src)
{
  const char *name = stp_get_string_parameter(src, "PageSize");
  if (name)
    {
      stp_mxml_node_t *node = get_media_size_xml(src);
      stp_mxml_node_t *xnode = stp_mxmlFindElement(node, node, "MediaSize",
						   "name", name, STP_MXML_DESCEND);
      if (xnode)
	{
	  stp_vars_fill_from_xmltree_ref(xnode->child, node, v);
	  return;
	}
      xnode = stp_mxmlFindElement(node, node, "MediaSize", "type", "default",
				  STP_MXML_DESCEND);
      if (xnode)
	{
	  stp_vars_fill_from_xmltree_ref(xnode->child, node, v);
	  return;
	}
    }
}
