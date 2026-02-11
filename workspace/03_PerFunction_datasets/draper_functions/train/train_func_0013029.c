session_query_glue(dns_session_t *session, dns_msg_question_t *q)
{
    dns_cache_rrset_t *rrset;

    plog(LOG_DEBUG, "%s: query glue: %s %s %s", MODULE,
         q->mq_name, dns_proto_class_string(q->mq_class), dns_proto_type_string(q->mq_type));

    if ((rrset = dns_cache_lookup(q, DNS_CACHE_GLUE, &session->sess_tls)) == NULL) {

        if ((rrset = dns_engine_query(q, session->sess_zone, &session->sess_tls)) == NULL)
            return NULL;

        dns_cache_register(rrset, DNS_CACHE_GLUE, &session->sess_tls);
    }

    if (session_validate_glue(rrset, session->sess_zone->z_name) < 0)
        return NULL;

    return rrset;
}
