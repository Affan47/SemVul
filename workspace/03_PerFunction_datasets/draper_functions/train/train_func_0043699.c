session_check_question_header(dns_header_t *header)
{
    if (ntohs(header->hdr_qdcount) != 1)
        return -1;
    if (ntohs(header->hdr_arcount) > 1)
        return -1;
    if (header->hdr_ancount != 0 || header->hdr_nscount != 0)
        return -1;

    return 0;
}
