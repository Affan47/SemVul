pk_backend_job_set_proxy (PkBackendJob	*job,
		      const gchar *proxy_http,
		      const gchar *proxy_https,
		      const gchar *proxy_ftp,
		      const gchar *proxy_socks,
		      const gchar *no_proxy,
		      const gchar *pac)
{
	g_return_if_fail (PK_IS_BACKEND_JOB (job));
	g_free (job->priv->proxy_http);
	g_free (job->priv->proxy_https);
	g_free (job->priv->proxy_ftp);
	g_free (job->priv->proxy_socks);
	g_free (job->priv->no_proxy);
	g_free (job->priv->pac);
	job->priv->proxy_http = g_strdup (proxy_http);
	job->priv->proxy_https = g_strdup (proxy_https);
	job->priv->proxy_ftp = g_strdup (proxy_ftp);
	job->priv->proxy_socks = g_strdup (proxy_socks);
	job->priv->no_proxy = g_strdup (no_proxy);
	job->priv->pac = g_strdup (pac);
}
