xmldoc_create_from_curve(const stp_curve_t *curve)
{
  stp_mxml_node_t *xmldoc;
  stp_mxml_node_t *rootnode;
  stp_mxml_node_t *curvenode;


  curvenode = stp_xmltree_create_from_curve(curve);
  if (curvenode == NULL)
    {
      stp_deprintf(STP_DBG_CURVE_ERRORS,
		   "xmldoc_create_from_curve: error creating curve node\n");
      return NULL;
    }

  xmldoc = stp_xmldoc_create_generic();
  if (xmldoc == NULL)
    {
      stp_deprintf(STP_DBG_CURVE_ERRORS,
		   "xmldoc_create_from_curve: error creating XML document\n");
      return NULL;
    }
  rootnode = xmldoc->child;
  if (rootnode == NULL)
    {
      stp_mxmlDelete(xmldoc);
      stp_deprintf(STP_DBG_CURVE_ERRORS,
		   "xmldoc_create_from_curve: error getting XML document root node\n");
      return NULL;
    }

  stp_mxmlAdd(rootnode, STP_MXML_ADD_AFTER, NULL, curvenode);

  return xmldoc;
}
