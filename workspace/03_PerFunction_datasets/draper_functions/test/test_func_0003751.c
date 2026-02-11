gdome_xml_a_name (GdomeAttr *self, GdomeException *exc) {
  Gdome_xml_Attr *priv = (Gdome_xml_Attr *)self;
  GdomeDOMString *ret = NULL;

  g_return_val_if_fail (priv != NULL, NULL);
  g_return_val_if_fail (GDOME_XML_IS_A (priv), NULL);
  g_return_val_if_fail (exc != NULL, NULL);

	if(gdome_xmlGetNs((xmlNode *)priv->n) != NULL)
		ret = gdome_xml_str_mkref_own (g_strdup_printf("%s:%s",
																									 (gchar *) gdome_xmlGetNsPrefix((xmlNode *)priv->n),
																									 (gchar *) gdome_xmlGetName((xmlNode *)priv->n)));
	else
		ret = gdome_xml_str_mkref_dup((gchar *)gdome_xmlGetName ((xmlNode *)priv->n));

  return ret;
}
