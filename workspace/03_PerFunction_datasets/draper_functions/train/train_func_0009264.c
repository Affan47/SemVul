hce_free(struct hostcache_entry *hce)
{
	g_assert(hce);
	g_assert(hce != NO_METADATA);

	WFREE(hce);
}
