gdome_xml_doc_createComment (GdomeDocument *self, GdomeDOMString *data, GdomeException *exc)
{
	Gdome_xml_Document *priv = (Gdome_xml_Document *)self;
	xmlNode *result = NULL;

	g_return_val_if_fail (priv != NULL, NULL);
	g_return_val_if_fail (GDOME_XML_IS_DOC (priv), NULL);
	g_return_val_if_fail (data != NULL, NULL);
	g_return_val_if_fail (exc != NULL, NULL);

	result = xmlNewComment (data->str);
	gdome_xmlSetOwner (result, priv->n);

	return (GdomeComment *)gdome_xml_n_mkref (result);
}
