session_query_glue(dns_session_t *session, dns_msg_question_t *q)
{
    dns_config_zone_t *zone;

    plog(LOG_DEBUG, "%s: query glue: %s %s %s", MODULE,
         q->mq_name, dns_proto_class_string(q->mq_class), dns_proto_type_string(q->mq_type));

    if ((zone = dns_config_find_zone(NULL, q->mq_name, q->mq_class)) == NULL)
        zone = session->sess_zone;

    return session_query_internal(session, zone, q);
}
