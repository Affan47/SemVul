request_redundant(struct interface *ifp,
                  const unsigned char *prefix, unsigned char plen,
                  unsigned short seqno, const unsigned char *id)
{
    struct resend *request;

    request = find_request(prefix, plen, NULL);
    if(request == NULL || resend_expired(request))
        return 0;

    if(memcmp(request->id, id, 8) == 0 &&
       seqno_compare(request->seqno, seqno) > 0)
        return 0;

    if(request->ifp != NULL && request->ifp != ifp)
        return 0;

    if(request->max > 0)

        return 1;

    if(timeval_minus_msec(&now, &request->time) <
       (ifp ? MIN(ifp->hello_interval, 1000) : 1000))

        return 1;

    return 0;
}
