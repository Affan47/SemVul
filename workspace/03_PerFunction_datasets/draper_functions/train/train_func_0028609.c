gnome_scan_job_set_sink (GnomeScanJob *job,
						 GnomeScanSink *sink)
{
	GnomeScanJobPrivate *priv = GET_PRIVATE(job);

	if (priv->sink)
		g_object_unref(priv->sink);

	priv->sink = g_object_ref(sink);
}
