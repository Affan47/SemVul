gdome_xml_df_query_interface (GdomeNode *self, const char *interface, GdomeException *exc)
{
	Gdome_xml_DocumentFragment *priv = (Gdome_xml_DocumentFragment *)self;

  g_return_val_if_fail (priv != NULL, NULL);
  g_return_val_if_fail (GDOME_XML_IS_DF (priv), NULL);
  g_return_val_if_fail (interface != NULL, NULL);
  g_return_val_if_fail (exc != NULL, NULL);

  if (!strcmp (interface, "Node") ||
      !strcmp (interface, "DocumentFragment") ||
      !strcmp (interface, "EventTarget")) {
    priv->refcnt++;
    return self;
  }
  else
    return NULL;
}
