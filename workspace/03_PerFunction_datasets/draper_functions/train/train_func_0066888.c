set_subnet_(ADF_AuthTable table,
           IPAddr *ip_addr,
           int subnet_bits,
           State new_state,
           int delete_children)
{
  uint32_t ip6[4];

  switch (ip_addr->family) {
    case IPADDR_INET4:
      return set_subnet(&table->base4, &ip_addr->addr.in4, 1, subnet_bits, new_state, delete_children);
    case IPADDR_INET6:
      split_ip6(ip_addr, ip6);
      return set_subnet(&table->base6, ip6, 4, subnet_bits, new_state, delete_children);
    case IPADDR_UNSPEC:

      if (subnet_bits != 0)
        return ADF_BADSUBNET;
      memset(ip6, 0, sizeof (ip6));
      if (set_subnet(&table->base4, ip6, 1, 0, new_state, delete_children) == ADF_SUCCESS &&
          set_subnet(&table->base6, ip6, 4, 0, new_state, delete_children) == ADF_SUCCESS)
        return ADF_SUCCESS;
      break;
  }

  return ADF_BADSUBNET;
}
