cache_rrset_plock(dns_cache_rrset_t **ptr, int nospin)
{
    void *p0, *np;

retry:
    p0 = *ptr;
    np = (void *) ((uintptr_t) p0 | CACHE_RRSET_PLOCK);

    if (p0 == NULL)
        return -1;

    if ((uintptr_t) p0 & CACHE_RRSET_PLOCK) {
        if (nospin)
            return -1;
        else {
            usleep(100);
            goto retry;
        }
    }

    if (!ATOMIC_CAS_PTR(ptr, p0, np))
        goto retry;

    return 0;
}
