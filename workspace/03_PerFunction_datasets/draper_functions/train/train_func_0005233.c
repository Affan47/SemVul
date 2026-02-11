gdome_xml_el_getElementsByTagNameNS (GdomeElement *self, GdomeDOMString *namespaceURI, GdomeDOMString *localName, GdomeException *exc)
{
  Gdome_xml_Element *priv = (Gdome_xml_Element *)self;

  g_return_val_if_fail (priv != NULL, NULL);
  g_return_val_if_fail (GDOME_XML_IS_EL (priv), NULL);
  g_return_val_if_fail (namespaceURI != NULL, NULL);
  g_return_val_if_fail (localName != NULL, NULL);
  g_return_val_if_fail (exc != NULL, NULL);

  return gdome_xml_nl_mkref ((GdomeNode*)self, localName, namespaceURI, GDOME_READWRITE_NODE);
}
