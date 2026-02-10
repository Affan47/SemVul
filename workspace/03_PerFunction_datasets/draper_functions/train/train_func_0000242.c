cache_rrset_new(dns_msg_question_t *q, dns_tls_t *tls)
{
    dns_cache_rrset_t *rrset;

    if ((rrset = (dns_cache_rrset_t *) dns_mpool_get(&CacheSetPool, tls->tls_id)) == NULL) {
        if ((rrset = cache_rrset_drain(tls)) == NULL)
            return NULL;
    }

    cache_rrset_reset(rrset, tls);

    if (cache_rrset_retain(rrset) < 0)
        plog(LOG_CRIT, "%s: new rrset retain failed. why?", __func__);

    return rrset;
}
