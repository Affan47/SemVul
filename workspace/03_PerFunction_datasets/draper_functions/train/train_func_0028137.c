gdome_xml_el_hasAttribute (GdomeElement *self, GdomeDOMString *name, GdomeException *exc)
{
  Gdome_xml_Node *priv = (Gdome_xml_Node *)self;
	xmlChar *val = NULL;
	xmlNs *ns = NULL;
	gchar **strs = NULL;

  g_return_val_if_fail (priv != NULL, 0);
  g_return_val_if_fail (GDOME_XML_IS_EL (priv), 0);
  g_return_val_if_fail (name != NULL, 0);
  g_return_val_if_fail (exc != NULL, 0);

  val = xmlGetProp (priv->n, name->str);

  if (val != NULL) {
    xmlFree(val);
		return 1;
	} else {
		strs = g_strsplit((gchar *)name->str, ":", 0);
		if (xmlStrEqual(strs[0], "xmlns"))
			ns = gdome_xmlGetNsDecl(priv->n, strs[1]);
		g_strfreev(strs);
		if (ns != NULL)
			return 1;
		else
			return 0;
	}
}
