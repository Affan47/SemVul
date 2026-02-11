camel_store_summary_touch (CamelStoreSummary *summary)
{
	g_return_if_fail (CAMEL_IS_STORE_SUMMARY (summary));

	g_rec_mutex_lock (&summary->priv->summary_lock);
	summary->priv->dirty = TRUE;
	g_rec_mutex_unlock (&summary->priv->summary_lock);
}
