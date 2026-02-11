readFromTAPSocket( n2n_edge_t * eee )
{

  u_char decrypted_msg[2048];
  size_t len;

  len = tuntap_read(&(eee->device), decrypted_msg, sizeof(decrypted_msg));

  if((len <= 0) || (len > sizeof(decrypted_msg)))
    traceEvent(TRACE_WARNING, "read()=%d [%d/%s]\n",
	       len, errno, strerror(errno));
  else {
    traceEvent(TRACE_INFO, "### Rx L2 Msg (%d) tun -> network", len);

    if ( eee->drop_ipv6_ndp && is_ip6_discovery( decrypted_msg, len ) ) {
      traceEvent(TRACE_WARNING, "Dropping unsupported IPv6 neighbour discovery packet");
    } else {
      send_packet2net(eee, (char*)decrypted_msg, len);
    }
  }
}
