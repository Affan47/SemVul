gdome_xml_cd_length (GdomeCharacterData *self, GdomeException *exc)
{
	Gdome_xml_CharacterData *priv = (Gdome_xml_CharacterData *)self;
	xmlChar *content;
	gulong length;

	g_return_val_if_fail (priv != NULL, 0L);
	g_return_val_if_fail (GDOME_XML_IS_CD (priv), 0L);
	g_return_val_if_fail (exc != NULL, 0L);

	content = xmlNodeGetContent (priv->n);
	length = gdome_utf16Length (content);
	g_free (content);
	return length;
}
