gdome_evt_mevnt_initMutationEventByCode (GdomeMutationEvent *self,
																				 guint32 typeArg,
																				 GdomeBoolean canBubbleArg,
																				 GdomeBoolean cancelableArg,
																				 GdomeNode *relatedNodeArg,
																				 GdomeDOMString *prevValueArg,
																				 GdomeDOMString *newValueArg,
																				 GdomeDOMString *attrNameArg,
																				 gushort attrChangeArg,
																				 GdomeException *exc)
{
	Gdome_evt_MutationEvent *priv = (Gdome_evt_MutationEvent *)self;

	g_return_if_fail (self != NULL);
  g_return_if_fail (exc != NULL);

	gdome_evt_evnt_initEventByCode ((GdomeEvent *)self, typeArg, canBubbleArg, cancelableArg, exc);
  priv->attrChange = attrChangeArg;
  if (attrNameArg != NULL) {
    gdome_xml_str_ref (attrNameArg);
    priv->attrName = attrNameArg;
  }
  if (newValueArg != NULL) {
    gdome_xml_str_ref (newValueArg);
    priv->newValue = newValueArg;
  }
  if (prevValueArg != NULL) {
    gdome_xml_str_ref (prevValueArg);
    priv->prevValue = prevValueArg;
  }
  if (relatedNodeArg != NULL) {
    gdome_xml_n_ref (relatedNodeArg, exc);
    priv->relatedNode = relatedNodeArg;
  }
}
