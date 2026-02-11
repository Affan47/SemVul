CacheLookupNoLocking(evalCache * pc, const cacheNodeDetail * e, float *arOut, float *arCubeful)
{
    uint32_t const l = GetHashKey(pc->hashMask, e);

#if CACHE_STATS
    ++pc->cLookup;
#endif
    if (!EqualKeys(pc->entries[l].nd_primary.key, e->key) || pc->entries[l].nd_primary.nEvalContext != e->nEvalContext) {
        if (!EqualKeys(pc->entries[l].nd_secondary.key, e->key) || pc->entries[l].nd_secondary.nEvalContext != e->nEvalContext) {
            return l;
        } else {
            cacheNodeDetail tmp = pc->entries[l].nd_primary;

            pc->entries[l].nd_primary = pc->entries[l].nd_secondary;
            pc->entries[l].nd_secondary = tmp;
        }
    }

#if CACHE_STATS
    ++pc->cHit;
#endif

    memcpy(arOut, pc->entries[l].nd_primary.ar, sizeof(float) * 5  );
    if (arCubeful)
        *arCubeful = pc->entries[l].nd_primary.ar[5];

    return CACHEHIT;
}
