gdome_xml_n_set_nodeValue (GdomeNode *self, GdomeDOMString *nodeValue, GdomeException *exc)
{
	Gdome_xml_Node *priv = (Gdome_xml_Node *)self;

	g_return_if_fail (priv != NULL);
	g_return_if_fail (GDOME_XML_IS_N (priv));
	g_return_if_fail (nodeValue != NULL);
  g_return_if_fail (exc != NULL);

  if (GDOME_ISREADONLY (priv)) {
    *exc = GDOME_NO_MODIFICATION_ALLOWED_ERR;
    return;
  }

	switch (gdome_xmlGetType(priv->n)) {
	case XML_ATTRIBUTE_NODE:
		gdome_xml_a_set_value ((GdomeAttr *)self, nodeValue, exc);
		break;
  case XML_PI_NODE:
    gdome_xml_pi_set_data ((GdomeProcessingInstruction *)self, nodeValue, exc);
    break;
	case XML_CDATA_SECTION_NODE:
	case XML_COMMENT_NODE:
  case XML_TEXT_NODE:
    gdome_xml_cd_set_data ((GdomeCharacterData *)self, nodeValue, exc);
		break;
	case XML_ELEMENT_NODE:
	case XML_ENTITY_NODE:
	case XML_ENTITY_REF_NODE:
	case XML_DOCUMENT_NODE:
	case XML_DOCUMENT_TYPE_NODE:
	case XML_DOCUMENT_FRAG_NODE:
  case XML_NOTATION_NODE:
  case XML_DTD_NODE:
  case XML_NAMESPACE_DECL:
		break;
	default:
		g_warning ("could not recognize the Node Type.");
  }
}
