mono_regstate_alloc_int (MonoRegState *rs, regmask_t allow)
{
	regmask_t mask = allow & rs->ifree_mask;

#if defined(__x86_64__) && defined(__GNUC__)
 {
	guint64 i;

	if (mask == 0)
		return -1;

	__asm__("bsfq %1,%0\n\t"
			: "=r" (i) : "rm" (mask));

	rs->ifree_mask &= ~ ((regmask_t)1 << i);
	return i;
 }
#else
	int i;

	for (i = 0; i < MONO_MAX_IREGS; ++i) {
		if (mask & ((regmask_t)1 << i)) {
			rs->ifree_mask &= ~ ((regmask_t)1 << i);
			return i;
		}
	}
	return -1;
#endif
}
