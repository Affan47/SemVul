gdome_xml_n_dispatchEvent (GdomeNode *self, GdomeEvent *evt, GdomeException *exc)
{
  Gdome_xml_Node *priv = (Gdome_xml_Node *)self;
  Gdome_evt_Event *ev_priv = (Gdome_evt_Event *)evt;

	g_return_val_if_fail (priv != NULL, FALSE);
	g_return_val_if_fail (GDOME_XML_IS_N (priv), FALSE);
	g_return_val_if_fail (evt != NULL, FALSE);
  g_return_val_if_fail (exc != NULL, FALSE);

  if (ev_priv->type == 0) {
    *exc = GDOME_EVENT_EXCEPTION + GDOME_UNSPECIFIED_EVENT_TYPE_ERR;
    return FALSE;
  }

  gdome_xml_n_ref (self, exc);
	ev_priv->target = self;
  gdome_evt_fireEvent (evt);
  gdome_xml_n_unref (self, exc);

	return !ev_priv->default_prevented;
}
