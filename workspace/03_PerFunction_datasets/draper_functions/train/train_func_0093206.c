prepare_ip4ip (packetinfo *pi)
{
    packetinfo pipi;
    memset(&pipi, 0, sizeof(packetinfo));
    config.pr_s.ip4ip_recv++;
    pipi.pheader = pi->pheader;
    pipi.packet = (pi->packet + pi->eth_hlen + (IP_HL(pi->ip4) * 4));
    pipi.end_ptr = pi->end_ptr;
    if (pi->ip4->ip_p == IP_PROTO_IP4) {
        prepare_ip4(&pipi);
        parse_ip4(&pipi);
        return;
    } else {
        prepare_ip6(&pipi);
        parse_ip6(&pipi);
        return;
    }
}
