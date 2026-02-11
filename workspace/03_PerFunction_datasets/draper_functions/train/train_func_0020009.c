broadcast_packet(char *packet, u_int packet_len,
                               struct peer_addr *sender,
                               n2n_sock_info_t * sinfo,
                               struct n2n_packet_header *hdr )
{
    size_t numsent=0;
    struct peer_info *scan;

    scan = known_peers;
    while(scan != NULL) {
        if((strcmp(scan->community_name, hdr->community_name) == 0)
           && (memcmp(sender, &scan->public_ip, sizeof(struct peer_addr)) ) )
        {
            int data_sent_len;
            size_t len = packet_len;

            data_sent_len = send_data( &(scan->sinfo), packet, &len, &scan->public_ip, 0);

            if(data_sent_len != len)
            {
                ++(supernode_stats.errors);
                traceEvent(TRACE_WARNING, "sendto() [sent=%d][attempted_to_send=%d] [%s]\n",
                           data_sent_len, len, strerror(errno));
            }
            else
            {
                ipstr_t buf;
                ipstr_t buf1;

                ++numsent;
                ++(supernode_stats.pkts);
                traceEvent(TRACE_INFO, "Sent multicast message to remote node [%s:%hu][mac=%s]",
                           intoa(ntohl(scan->public_ip.addr_type.v4_addr), buf, sizeof(buf)),
                           ntohs(scan->public_ip.port),
                           macaddr_str(scan->mac_addr, buf1, sizeof(buf1)));
            }
        }

        scan = scan->next;
    }


    return numsent;
}
