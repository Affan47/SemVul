hostname_thread_free (HostnameThread *ht)
{
	g_return_if_fail (ht != NULL);

	nm_log_dbg (LOGD_DNS, "(%p) freeing reverse-lookup thread", ht);

	X_MUTEX_CLEAR (ht->lock);
	memset (ht, 0, sizeof (HostnameThread));
	g_free (ht);
}
