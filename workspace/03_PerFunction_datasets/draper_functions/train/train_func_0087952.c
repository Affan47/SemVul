dns_query_start(struct sockaddr *to, dns_msg_question_t *q, uint16_t msgid, dns_tls_t *tls)
{
    int s;

    if ((s = query_connect(to, tls)) < 0)
        return -1;
    if (query_send(s, q, msgid) < 0) {
        close(s);
        return -1;
    }

    return s;
}
