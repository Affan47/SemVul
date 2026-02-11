gdome_xml_doc_createProcessingInstruction (GdomeDocument *self, GdomeDOMString *target, GdomeDOMString *data, GdomeException *exc)
{
	Gdome_xml_Document *priv = (Gdome_xml_Document *)self;
	xmlNode *result;

	g_return_val_if_fail (priv != NULL, NULL);
	g_return_val_if_fail (GDOME_XML_IS_DOC (priv), NULL);
	g_return_val_if_fail (target != NULL, NULL);
	g_return_val_if_fail (data != NULL, NULL);
	g_return_val_if_fail (exc != NULL, NULL);

	result = xmlNewPI (target->str, data->str);
	gdome_xmlSetOwner (result, priv->n);

	return (GdomeProcessingInstruction *)gdome_xml_n_mkref (result);
}
