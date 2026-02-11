cache_rrset_drain_hash(cache_hash_t *hash, dns_tls_t *tls)
{
    int i;
    unsigned r;
    dns_cache_rrset_t *rrset;

    r = xarc4random(&tls->tls_arctx);

    for (i = 0; i < NELEMS(hash->hash_array); i++, r++) {


        r %= NELEMS(hash->hash_array);
        if ((rrset = cache_rrset_retain2(&hash->hash_array[r], NOSPIN)) == NULL)
            continue;

        cache_rrset_invalidate(rrset, hash, r, tls);
        if (CACHE_RRSET_REFS(rrset) == 1)
            return rrset;

        cache_rrset_release(rrset, tls);
    }

    return NULL;
}
