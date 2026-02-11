wmove(void *ptr, size_t size)
{
	zone_t *zone = walloc_get_zone(zalloc_round(size), FALSE);

	if G_UNLIKELY(walloc_stopped)
		return ptr;

	g_assert(zone != NULL);

	return zmove(zone, ptr);
}
