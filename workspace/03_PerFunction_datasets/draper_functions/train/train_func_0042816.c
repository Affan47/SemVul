dhcp_extract_router_msg (struct buffer *ipbuf)
{
  struct dhcp_full *df = (struct dhcp_full *) BPTR (ipbuf);
  const int optlen = BLEN (ipbuf) - (sizeof (struct openvpn_iphdr) + sizeof (struct openvpn_udphdr) + sizeof (struct dhcp));

  if (optlen >= 0
      && df->ip.protocol == OPENVPN_IPPROTO_UDP
      && df->udp.source == htons (BOOTPS_PORT)
      && df->udp.dest == htons (BOOTPC_PORT)
      && df->dhcp.op == BOOTREPLY
      && get_dhcp_message_type (&df->dhcp, optlen) == DHCPACK)
    {

      const in_addr_t ret = do_extract (&df->dhcp, optlen);


      df->udp.check = htons (udp_checksum ((uint8_t *) &df->udp,
					   sizeof (struct openvpn_udphdr) + sizeof (struct dhcp) + optlen,
					   (uint8_t *)&df->ip.saddr,
					   (uint8_t *)&df->ip.daddr));

      if (ret)
	{
	  struct gc_arena gc = gc_new ();
	  msg (D_ROUTE, "Extracted DHCP router address: %s", print_in_addr_t (ret, 0, &gc));
	  gc_free (&gc);
	}

      return ret;
    }
  else
    return 0;
}
