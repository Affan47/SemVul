hashlist_count (HASH * h, void *key)
{
    hashlist_t *hl;

    ASSERT (key != 0);
    hl = hash_lookup (h, key);
#if DEBUG
    if (hl)
	ASSERT (hashlist_validate (hl));
#endif
    return (hl ? hl->count : 0);
}
