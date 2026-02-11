find_peer_destination(n2n_edge_t * eee,
                                 const u_char *mac_address,
                                 struct peer_addr *destination) {
  const struct peer_info *scan = eee->known_peers;
  macstr_t mac_buf;
  ipstr_t ip_buf;
  int retval=0;

  traceEvent(TRACE_INFO, "Searching destination peer for MAC %02X:%02X:%02X:%02X:%02X:%02X",
	     mac_address[0] & 0xFF, mac_address[1] & 0xFF, mac_address[2] & 0xFF,
	     mac_address[3] & 0xFF, mac_address[4] & 0xFF, mac_address[5] & 0xFF);

  while(scan != NULL) {
    traceEvent(TRACE_INFO, "Evaluating peer [MAC=%02X:%02X:%02X:%02X:%02X:%02X][ip=%s:%hu]",
	       scan->mac_addr[0] & 0xFF, scan->mac_addr[1] & 0xFF, scan->mac_addr[2] & 0xFF,
	       scan->mac_addr[3] & 0xFF, scan->mac_addr[4] & 0xFF, scan->mac_addr[5] & 0xFF,
	       intoa(ntohl(scan->public_ip.addr_type.v4_addr), ip_buf, sizeof(ip_buf)),
	       ntohs(scan->public_ip.port));

    if((scan->last_seen > 0) &&
       (memcmp(mac_address, scan->mac_addr, 6) == 0))
      {
        memcpy(destination, &scan->public_ip, sizeof(struct sockaddr_in));
        retval=1;
        break;
      }
    scan = scan->next;
  }

  if ( 0 == retval )
    {
      memcpy(destination, &(eee->supernode), sizeof(struct sockaddr_in));
    }

  traceEvent(TRACE_INFO, "find_peer_address(%s) -> [socket=%s:%hu]",
             macaddr_str( (char *)mac_address, mac_buf, sizeof(mac_buf)),
             intoa(ntohl(destination->addr_type.v4_addr), ip_buf, sizeof(ip_buf)),
             ntohs(destination->port));

  return retval;
}
