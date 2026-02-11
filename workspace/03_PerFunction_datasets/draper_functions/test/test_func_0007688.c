rewrite_node_address_for_bridge(const bridge_info_t *bridge, node_t *node)
{


  tor_addr_t addr;

  if (node->ri) {
    routerinfo_t *ri = node->ri;
    tor_addr_from_ipv4h(&addr, ri->addr);

    if ((!tor_addr_compare(&bridge->addr, &addr, CMP_EXACT) &&
         bridge->port == ri->or_port) ||
        (!tor_addr_compare(&bridge->addr, &ri->ipv6_addr, CMP_EXACT) &&
         bridge->port == ri->ipv6_orport)) {

    } else {
      if (tor_addr_family(&bridge->addr) == AF_INET) {
        ri->addr = tor_addr_to_ipv4h(&bridge->addr);
        tor_free(ri->address);
        ri->address = tor_dup_ip(ri->addr);
        ri->or_port = bridge->port;
        log_info(LD_DIR,
                 "Adjusted bridge routerinfo for '%s' to match configured "
                 "address %s:%d.",
                 ri->nickname, ri->address, ri->or_port);
      } else if (tor_addr_family(&bridge->addr) == AF_INET6) {
        tor_addr_copy(&ri->ipv6_addr, &bridge->addr);
        ri->ipv6_orport = bridge->port;
        log_info(LD_DIR,
                 "Adjusted bridge routerinfo for '%s' to match configured "
                 "address %s:%d.",
                 ri->nickname, fmt_addr(&ri->ipv6_addr), ri->ipv6_orport);
      } else {
        log_err(LD_BUG, "Address family not supported: %d.",
                tor_addr_family(&bridge->addr));
        return;
      }
    }


    ri->ipv6_preferred = tor_addr_family(&bridge->addr) == AF_INET6;


    if (!tor_addr_is_null(&ri->ipv6_addr))
    {
      tor_addr_port_t ap;
      router_get_pref_orport(ri, &ap);
      log_notice(LD_CONFIG,
                 "Bridge '%s' has both an IPv4 and an IPv6 address.  "
                 "Will prefer using its %s address (%s:%d).",
                 ri->nickname,
                 ri->ipv6_preferred ? "IPv6" : "IPv4",
                 fmt_addr(&ap.addr), ap.port);
    }
  }
  if (node->rs) {
    routerstatus_t *rs = node->rs;
    tor_addr_from_ipv4h(&addr, rs->addr);

    if (!tor_addr_compare(&bridge->addr, &addr, CMP_EXACT) &&
        bridge->port == rs->or_port) {

    } else {
      rs->addr = tor_addr_to_ipv4h(&bridge->addr);
      rs->or_port = bridge->port;
      log_info(LD_DIR,
               "Adjusted bridge routerstatus for '%s' to match "
               "configured address %s:%d.",
               rs->nickname, fmt_addr(&bridge->addr), rs->or_port);
    }
  }
}
