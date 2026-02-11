get_sentinel(struct entry_alloc *ea, unsigned level, bool which)
{
	return get_entry(ea, which ? level : NR_CACHE_LEVELS + level);
}
