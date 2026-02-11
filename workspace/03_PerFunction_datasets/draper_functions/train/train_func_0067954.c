gda_report_engine_dispose (GObject *object)
{
	GdaReportEngine *eng = (GdaReportEngine *) object;

	g_return_if_fail (GDA_IS_REPORT_ENGINE (eng));


	if (eng->priv) {
		if (eng->priv->objects) {
			g_hash_table_destroy (eng->priv->objects);
			eng->priv->objects = NULL;
		}

		if (eng->priv->doc) {
			xmlFreeDoc (eng->priv->doc);
			eng->priv->doc = NULL;
		}

		if (eng->priv->spec) {
			xmlFreeNode (eng->priv->spec);
			eng->priv->spec = NULL;
		}

		g_free (eng->priv->output_dir);

		g_free (eng->priv);
		eng->priv = NULL;
	}


	parent_class->dispose (object);
}
