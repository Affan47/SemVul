session_query_internal(dns_session_t *session, dns_config_zone_t *zone, dns_msg_question_t *q)
{
    dns_cache_rrset_t *rrset;

    plog(LOG_DEBUG, "%s: internal query: %s %s %s (zone \"%s\")",
         MODULE, q->mq_name,
         dns_proto_class_string(q->mq_class), dns_proto_type_string(q->mq_type),
         zone->z_name);

    if ((rrset = dns_cache_lookup(q, DNS_CACHE_IZL(zone->z_id), &session->sess_tls)) == NULL) {
        if ((rrset = dns_engine_query(q, zone, &session->sess_tls)) == NULL)
            return NULL;

        dns_cache_register(rrset, DNS_CACHE_IZL(zone->z_id), &session->sess_tls);
    }

    return rrset;
}
