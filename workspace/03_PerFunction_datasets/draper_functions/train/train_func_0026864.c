libnet_build_tcp(u_short sp, u_short dp, u_long seq, u_long ack, u_char control,
            u_short win, u_short urg, const u_char *payload, int payload_s,
            u_char *buf)
{
    struct libnet_tcp_hdr tcp_hdr;

    if (!buf)
    {
        return (-1);
    }

    tcp_hdr.th_sport   = htons(sp);
    tcp_hdr.th_dport   = htons(dp);
    tcp_hdr.th_seq     = htonl(seq);
    tcp_hdr.th_ack     = htonl(ack);
    tcp_hdr.th_flags   = control;
    tcp_hdr.th_x2      = 0;
    tcp_hdr.th_off     = 5;
    tcp_hdr.th_win     = htons(win);
    tcp_hdr.th_sum     = 0;
    tcp_hdr.th_urp     = urg;

    if (payload && payload_s)
    {


        memcpy(buf + LIBNET_TCP_H, payload, payload_s);
    }
    memcpy((u_char *)buf, (u_char *)&tcp_hdr, sizeof(tcp_hdr));
    return (1);
}
