gda_report_engine_run_as_doc (GdaReportEngine *engine, GError **error)
{
	xmlNodePtr retnode;
	xmlDocPtr doc;
	g_return_val_if_fail (GDA_IS_REPORT_ENGINE (engine), NULL);
	g_return_val_if_fail (engine->priv, NULL);
	g_return_val_if_fail (engine->priv->spec, NULL);

	retnode = gda_report_engine_run_as_node (engine, error);
	if (!retnode)
		return NULL;
	if (engine->priv->doc)
		doc = xmlCopyDoc (engine->priv->doc, 1);
	else
		doc = xmlNewDoc (BAD_CAST "1.0");
	xmlDocSetRootElement (doc, retnode);
	return doc;
}
