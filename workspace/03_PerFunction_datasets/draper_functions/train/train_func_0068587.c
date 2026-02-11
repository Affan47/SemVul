hikset_iter_check(const hikset_iter_t * const hxi)
{
	g_assert(hxi != NULL);
	g_assert(HIKSET_ITER_MAGIC == hxi->magic);
	hikset_check(hxi->hx);
}
