gdome_xml_n_hasAttributes (GdomeNode *self, GdomeException *exc) {
	Gdome_xml_Node *priv = (Gdome_xml_Node *)self;

	g_return_val_if_fail (priv != NULL, 0);
	g_return_val_if_fail (GDOME_XML_IS_N (priv), 0);
	g_return_val_if_fail (exc != NULL, 0);

	if (GDOME_XML_IS_EL (priv))
		return (gdome_xmlGetAttrList (priv->n) != NULL);
	else
    return FALSE;
}
