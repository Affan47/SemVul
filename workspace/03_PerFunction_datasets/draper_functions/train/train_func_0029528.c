send_packet(struct sockaddr *sin, int sinlen,
                const unsigned char *dest, int hopcount,
                const unsigned char *buf, size_t bufsize)
{
    unsigned char nonce[4];

    if(hopcount <= 0)
        return 0;

    memcpy(nonce, &myseqno, 4);
    myseqno++;

    return really_send_packet(sin, sinlen,
                              hopcount, hopcount, nonce, myid, dest,
                              buf, bufsize);
}
