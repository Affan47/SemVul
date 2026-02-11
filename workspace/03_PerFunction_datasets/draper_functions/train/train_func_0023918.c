gdome_xml_doc_createElement (GdomeDocument *self, GdomeDOMString *tagName, GdomeException *exc)
{
	Gdome_xml_Document *priv = (Gdome_xml_Document *)self;
	xmlNode *result = NULL;

	g_return_val_if_fail (priv != NULL, NULL);
	g_return_val_if_fail (GDOME_XML_IS_DOC (priv), NULL);
	g_return_val_if_fail (tagName != NULL, NULL);
	g_return_val_if_fail (exc != NULL, NULL);

	result = xmlNewDocNode (priv->n, NULL, tagName->str, NULL);

	return (GdomeElement *)gdome_xml_n_mkref (result);
}
