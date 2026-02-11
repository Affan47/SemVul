session_request_proc(dns_session_t *session, dns_sock_buf_t *sbuf)
{
    int rcode;
    dns_msg_question_t *q;

    if ((rcode = session_read_question(session, sbuf)) != DNS_RCODE_NOERROR)
        goto error;

    q = &session->sess_question;
    if ((session->sess_zone = dns_config_find_zone(&session->sess_zone_exact,
                                                   q->mq_name, q->mq_class)) == NULL) {
        rcode = DNS_RCODE_SERVFAIL;
        goto error;
    }

    plog(LOG_DEBUG, "%s: opcode = %d", MODULE, session->sess_opcode);

    switch (session->sess_opcode) {
    case DNS_OP_QUERY:
        if ((rcode = session_request_query(session, sbuf)) != DNS_RCODE_NOERROR)
            goto error;
        break;

    case DNS_OP_NOTIFY:
        if ((rcode = session_request_notify(session, sbuf)) != DNS_RCODE_NOERROR)
            goto error;
        break;
    }

    return 0;

error:
    if (rcode > 0 && session_make_error(sbuf, session, rcode, 0) >= 0)
        session_send_response(sbuf);
    else
        session_send_finish(sbuf);

    ATOMIC_INC(&SessionStats.stat_error);

    return -1;
}
