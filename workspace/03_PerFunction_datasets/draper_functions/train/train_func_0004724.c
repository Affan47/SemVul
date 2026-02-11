session_make_response(dns_sock_buf_t *sbuf, dns_session_t *session, dns_cache_rrset_t *rrset_an, dns_cache_rrset_t *rrset_ns, int rcode, int flags)
{
    int resmax;
    dns_msg_handle_t handle;

    plog(LOG_DEBUG, "%s: send response", MODULE);

    resmax = SOCK_MSGMAX(sbuf->sb_sock);
    resmax = session_max_payload_size(session, resmax);

    if (dns_msg_write_open(&handle, sbuf->sb_buf, resmax) < 0) {
        plog(LOG_ERR, "%s: dns_msg_write_open() failed", MODULE);
        return -1;
    }

    if (session_write_header(session, &handle, sbuf->sb_buf, rcode, flags) < 0)
        return -1;


    if (rrset_an != NULL) {
        session_write_resources(session, &handle, &rrset_an->rrset_list_cname, DNS_MSG_RESTYPE_ANSWER);
        session_write_resources_rr(session, &handle, &rrset_an->rrset_list_answer, DNS_MSG_RESTYPE_ANSWER);
    }


    if (rrset_ns != NULL) {
        session_write_resources_rr(session, &handle, &rrset_ns->rrset_list_answer, DNS_MSG_RESTYPE_AUTHORITY);
        session_write_resources_ar(session, &handle, &rrset_ns->rrset_list_answer, DNS_TYPE_A);
        session_write_resources_ar(session, &handle, &rrset_ns->rrset_list_answer, DNS_TYPE_AAAA);
    }


    if (session->sess_extflags & SESSION_EDNS_REQUESTED)
        session_write_resources_opt(session, &handle);

    if ((sbuf->sb_buflen = dns_msg_write_close(&handle)) < 0) {
        plog(LOG_ERR, "%s: dns_msg_write_close() failed", MODULE);
        return -1;
    }

    return 0;
}
