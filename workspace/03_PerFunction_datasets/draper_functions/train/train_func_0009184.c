check_subnet_conflict (const in_addr_t ip,
		       const in_addr_t netmask,
		       const char *prefix)
{
  struct gc_arena gc = gc_new ();
  in_addr_t lan_gw = 0;
  in_addr_t lan_netmask = 0;

  if (get_default_gateway (&lan_gw, &lan_netmask))
    {
      const in_addr_t lan_network = lan_gw & lan_netmask;
      const in_addr_t network = ip & netmask;


      if ((network & lan_netmask) == lan_network
	  || (lan_network & netmask) == network)
	{
	  msg (M_WARN, "WARNING: potential %s subnet conflict between local LAN [%s/%s] and remote VPN [%s/%s]",
	       prefix,
	       print_in_addr_t (lan_network, 0, &gc),
	       print_in_addr_t (lan_netmask, 0, &gc),
	       print_in_addr_t (network, 0, &gc),
	       print_in_addr_t (netmask, 0, &gc));
	}
    }
  gc_free (&gc);
}
